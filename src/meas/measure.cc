// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "meas/measure.h"
#include "common/utils.h"

namespace mht_measurement {

Measurement::Measurement(){}

Measurement::Measurement(const string& param_path){
    
    LOG_INFO("Construct Measurement Space");

    load_parameters(param_path);   
}

Measurement::Measurement(const string& param_path, const std::shared_ptr<mht_common::Random>& random){
    
    LOG_INFO("Construct Measurement Space");

    load_parameters(param_path);   
    
    set_random(random);

    seq_data measures, targets, noises;
    generate_measures(measures, targets, noises);
}

void Measurement::load_parameters(const string& param_path){

    auto meas_params = load_param_file(param_path);

    if(meas_params.size()){
        for(auto it=meas_params.begin(); it!=meas_params.end(); it++){
            _meas_params.set_params(it->first, it->second);
        }
    }
}

void Measurement::set_random(const std::shared_ptr<mht_common::Random>& random){
    
    _random = random;
}

void Measurement::generate_noises(seq_data& noise_pos){

    int expect_nosie = _meas_params.get_expect_noise();
    int sample_num = _meas_params.get_sample_num();
    int scene_dim = _meas_params._SCENE_DIMENSION;
    float scene_range = _meas_params._SCENE_RANGE;

    vector<int> noise_nums;
    _random->get_possion_randoms(noise_nums, expect_nosie, sample_num);

    auto total_noise = accumulate(noise_nums.begin(), noise_nums.end(), 0);

    vector<float> noise_pos_list;
    _random->get_uniform_randoms(noise_pos_list, 0, scene_range, total_noise*scene_dim);

    int start_idx=0;
    noise_pos.resize(sample_num);
    for(int i = 0; i < noise_nums.size(); i++){
        noise_pos[i].resize(noise_nums[i]);
        
        for(int j = 0; j < noise_nums[i]; j++){

            Eigen::VectorXf temp_noise_pos(scene_dim);
            for(int k = 0; k < _meas_params._SCENE_DIMENSION; k++)
                temp_noise_pos(k) = noise_pos_list[start_idx++];

            noise_pos[i][j] = temp_noise_pos;
        }
    }
}

void Measurement::generate_targets(seq_data& targets_state){

    int sample_num = _meas_params.get_sample_num();
    float delta_t = _meas_params._SAMPLE_INTERVAL;
    int scene_dim = _meas_params._SCENE_DIMENSION;
    float scene_range = _meas_params._SCENE_RANGE;
    int target_num = _meas_params._SCENE_TARGET;
    string target_motion = _meas_params._TARGET_MOTION;
    float target_speed_range = _meas_params._INIT_SPEED_RANGE;

    vector<float> init_target_pos, init_target_veloc;
    _random->get_uniform_randoms(init_target_pos, 0, scene_range, target_num*scene_dim);
    _random->get_uniform_randoms(init_target_veloc, 0, target_speed_range, target_num*scene_dim);

    targets_state.assign(sample_num, vector<Eigen::VectorXf>(target_num, Eigen::VectorXf(scene_dim*2)));
    auto motion_trans_mat = mht_common::Motion::CV(scene_dim, delta_t);
    
    for(int i=0; i<target_num; i++){
        for(int j=0; j<sample_num; j++){
            if(j == 0){
                for(int k=0; k<scene_dim; k++){
                    targets_state[j][i](k) = init_target_pos[k];
                    targets_state[j][i](k+scene_dim) = init_target_veloc[k];
                }
            }
            else{
                targets_state[j][i] = motion_trans_mat*targets_state[j-1][i];
            }
        }
    }
}

void Measurement::generate_measures(seq_data& measures, seq_data& targets, seq_data& noises){

    generate_noises(noises);
    generate_targets(targets);
        
    if(targets.size() != noises.size()){
        throw "The Length of Target is not equal with Noise!";
    }

    

    int data_len = targets.size();

    measures.resize(data_len);
    // for(int )

    
}

void M

std::map<string, string> Measurement::load_param_file(const string& param_path){

    LOG_INFO("Loading Parameters from {}", param_path);
    
    std::fstream param_stream(param_path, std::fstream::in);
    if(!param_stream.is_open()){
        throw "Open parameter file failed!";
    }

    std::map<string, string> meas_params;
    string params;
    while(param_stream.good()){

        std::getline(param_stream, params);
        if(params.size() == 0 || (params[0] == '/' && params[1] == '/')) continue;

        auto key_value = mht_common::str_split(params, "=");
        meas_params[key_value[0]] = key_value[1];

        // for(auto it: key_value) std::cout<< it <<'\t';
        // std::cout<<std::endl;
    }
    param_stream.close();

    return meas_params;
}

Measurement::~Measurement(){}

}

