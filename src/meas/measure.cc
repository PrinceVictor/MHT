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

void Measurement::load_parameters(const string& param_path){

    auto meas_params = load_param_file(param_path);

    if(meas_params.size()){
        for(auto it=meas_params.begin(); it!=meas_params.end(); it++){
            _meas_params.set_params(it->first, it->second);
        }
    }
}

void Measurement::set_random(std::shared_ptr<mht_common::Random>& random){
    
    _random = random;
}

void Measurment::generate_measures(){

    int expect_nosie = _meas_params.get_expect_noise();
    int sample_num = _meas_params.get_sample_num()

    vector<int> noise_nums;
    _random->get_possion_randoms(noise_nums, expect_nosie, sample_num);

    auto total_noise = accumulated(noise_nums.begin(), noise_nums.end(), 0);

    vector<float> noise_pos_list;
    _random->get_uniform_randoms(noise_, 0, 100, total_noise*2);

    int start_idx=0;
    vector<vector<Eigen::Vector2f>> noise_pos(sample_num);
    for(int i = 0; i < noise_nums.size(); ++i){
        noise_pos[i].resize(noise_nums[i]);
        
        for(int j = 0; j < noise_nums[i]; ++j){
            noise_pos[i][j] << noise_pos_list[start_idx], noise_pos_list[start_idx+1];
            start_idx += 2;
        }
    }    
    
}

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

        auto key_value = mht_utils::str_split(params, "=");
        meas_params[key_value[0]] = key_value[1];

        // for(auto it: key_value) std::cout<< it <<'\t';
        // std::cout<<std::endl;
    }
    param_stream.close();

    return meas_params;
}

Measurement::~Measurement(){}

}

