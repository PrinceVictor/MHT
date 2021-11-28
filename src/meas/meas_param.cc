// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/27
// Author: Hongbin Zhou

#include "meas/meas_param.h"

namespace mht_measurement {

const static std::vector<string> MeasParams::_keys = 
    {"SCENE_DIMENSION", "SCENE_TYPE", "SCENE_RANGE", 
     "SCENE_TARGET", "TARGET_MOTION", "SAMPLE_INTERVAL", 
     "TIME_START", "TIME_END", "INIT_SPEED_RANGE", "EXPECT_NOISE"};

MeasParams::MeasParams(){

    LOG_INFO("INIT THE MEASUREMENT PARAMETERS");

    for(int i=0; i<_keys.size(); i++){
        _params[_keys[i]] = i;
    }
    
}

int MeasParams::get_sample_num(){

    return std::floor((_TIME_END-_TIME_START)/_SAMPLE_INTERVAL);
}

int MeasParams::get_expect_noise(){
    
    return _EXPECT_NOISE;
}

void MeasParams::set_params(const string& key, const string& value){

    switch(_param_key_dict[key]){
        case 0: _SCENE_DIMENSION=std::stoi(value);break;
        case 1: _SCENE_TYPE=value;break;
        case 2: _SCENE_RANGE=std::stof(value);break;
        case 3: _SCENE_TARGET=std::stoi(value);break;
        case 4: _TARGET_MOTION=value;break;
        case 5: _SAMPLE_INTERVAL=std::stof(value);break;
        case 6: _TIME_START=std::stof(value);break;
        case 7: _TIME_END=std::stof(value);break;
        case 8: _INIT_SPEED_RANGE=std::stof(value);break;
        case 9: _EXPECT_NOISE=std::stoi(value);break;
    }
}

}