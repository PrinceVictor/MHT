// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "meas/measure.h"
#include "common/utils.h"

namespace mht_measurement {

Measurement::Measurement(){}

Measurement::Measurement(const string& param_path):_params(param_path){
    
    LOG_INFO("Construct Measurement Space");

    generateMeasures();
}

const std::map<float, vector<Eigen::VectorXf>>& Measurement::get_measurements(){

    return _measures;
}

void Measurement::generateMeasures(){

    _targets.clear(); _noises.clear();
    seq_data measures;

    generateNoises();
    generateTarget();
        
    if(_targets.size() != _noises.size()){
        throw "The Length of Target is not equal with Noise!";
    }

    int seq_len = _targets.size();
    int add_noise_num = seq_len*_targets[0].size();
    float noise_std = _params._MEASUREMENT_NOISE;
    int scene_dim = _params._SCENE_DIMENSION;
    float time_start = _params._TIME_START;
    float delta_t = _params._SAMPLE_INTERVAL;

    vector<float> add_noises(add_noise_num);
    Random::getNormalRandoms(add_noises, 0, noise_std, add_noise_num*scene_dim);
    
    int start_idx=0;
    measures.resize(seq_len);
    for(int i = 0; i < seq_len; i++){
        measures[i].resize(_noises[i].size()+_targets[i].size());
        
        Eigen::VectorXf temp_X(scene_dim);
        for(int j = 0; j < _targets[i].size(); j++){
            for(int k = 0; k < scene_dim; k++){
                temp_X(k) = _targets[i][j](k)+add_noises[start_idx++];
            }
            measures[i][j] = temp_X;
        }

        for(int j=0; j<_noises[i].size(); j++){
            measures[i][j+_targets[i].size()] = _noises[i][j];
        }
        _measures[time_start+i*delta_t].swap(measures[i]);
    }
}

void Measurement::generateNoises(){

    int expect_nosie = _params._EXPECT_NOISE;
    int sample_num = _params.getSampleNum();
    int scene_dim = _params._SCENE_DIMENSION;
    float scene_range = _params._SCENE_RANGE;

    vector<int> noise_nums;
    Random::getPossionRandoms(noise_nums, expect_nosie, sample_num);

    auto total_noise = accumulate(noise_nums.begin(), noise_nums.end(), 0);

    vector<float> noise_pos_list;
    Random::getUniformRandoms(noise_pos_list, 0, scene_range, total_noise*scene_dim);

    int start_idx=0;
    _noises.resize(sample_num);
    for(int i = 0; i < noise_nums.size(); i++){
        _noises[i].resize(noise_nums[i]);
        
        for(int j = 0; j < noise_nums[i]; j++){

            Eigen::VectorXf temp_noise_pos(scene_dim);
            for(int k = 0; k < _params._SCENE_DIMENSION; k++)
                temp_noise_pos(k) = noise_pos_list[start_idx++];

            _noises[i][j] = temp_noise_pos;
            #ifdef USE_DEBUG
                LOG_INFO("Time:{} Noise id:{}  x:{:.3f} y{:.3f}", i, j, _noises[i][j](0),  _noises[i][j](1));
            #endif
        }
    }
}

void Measurement::generateTarget(){

    int sample_num = _params.getSampleNum();
    float delta_t = _params._SAMPLE_INTERVAL;
    int scene_dim = _params._SCENE_DIMENSION;
    float scene_range = _params._SCENE_RANGE;
    int target_num = _params._SCENE_TARGET;
    string target_motion = _params._TARGET_MOTION;
    float target_speed_range = _params._INIT_SPEED_RANGE;

    vector<float> init_target_pos, init_target_veloc;
    Random::getUniformRandoms(init_target_pos, 0, scene_range, target_num*scene_dim);
    Random::getUniformRandoms(init_target_veloc, 0, target_speed_range, target_num*scene_dim);

    _targets.assign(sample_num, vector<Eigen::VectorXf>(target_num, Eigen::VectorXf(scene_dim*2)));
    auto motion_trans_mat = mht_common::Motion::CV(scene_dim, delta_t);
    
    
    for(int i=0; i<sample_num; i++){
        for(int j=0; j<target_num; j++){
            if(i == 0){
                for(int k=0; k<scene_dim; k++){
                    _targets[i][j](k) = init_target_pos[k+j*scene_dim];
                    _targets[i][j](k+scene_dim) = init_target_veloc[k+j*scene_dim];
                }
            }
            else{
                _targets[i][j] = motion_trans_mat*_targets[i-1][j];
            }
            #ifdef USE_DEBUG
                LOG_INFO("Time:{} Target id:{} x:{:.3f} y{:.3f}", j, i, _targets[i][j](0), _targets[i][j](1));
            #endif
        }
    }
}

Measurement::~Measurement(){}

}

