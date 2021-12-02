// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/30
// Author: Hongbin Zhou

#include "tracker/mht_param.h"

namespace mht_tracker {

const std::vector<string> MHTParams::_keys = 
    {"SCENE_DIMENSION", "P_DETECTION"};

MHTParams::MHTParams(){
    
    LOG_INFO("INIT THE MHT PARAMETERS");

    init_key_dict(_keys);
}

MHTParams::MHTParams(const string& param_path){

    LOG_INFO("INIT THE MHT PARAMETERS");

    init_key_dict(_keys);

    load_parameters(param_path);
}

void MHTParams::set_params(const string& key, const string& value){

    if(_param_key_dict.count(key) == 0) return;
    switch(_param_key_dict[key]){
        case 0: _SCENE_DIMENSION=std::stoi(value);break;
        case 1: _P_DETECTION=std::stof(value);break;
    }
}

}