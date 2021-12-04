// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/30
// Author: Hongbin Zhou

#include "tracker/mhtparam.h"

namespace mht_tracker {

const std::vector<string> MHTParams::_keys = 
    {"SCENE_DIMENSION", "N_SCAN", "P_DETECTION", "SAMPLE_INTERVAL", "POSITION_ERROR",
     "VELOCITY_ERROR", "MEASUREMENT_NOISE", "STATE_ERROR", "EXPECT_NOISE",
     "TARGET_DENSITY", "TRACK_GATE_THRES", "TRACK_SCORE_DEL_THRES", "TRACK_SCORE_CONF_THRES"};

MHTParams::MHTParams(){
    
    LOG_INFO("INIT THE MHT PARAMETERS");

    initKeyDict(_keys);
}

MHTParams::MHTParams(const string& param_path){

    LOG_INFO("INIT THE MHT PARAMETERS");

    initKeyDict(_keys);

    loadParameters(param_path);
}

void MHTParams::setParams(const string& key, const string& value){

    if(_param_key_dict.count(key) == 0) return;
    switch(_param_key_dict[key]){
        case 0: _SCENE_DIMENSION=std::stoi(value);break;
        case 1: N_SCAN=std::stoi(value);break;
        case 2: _P_DETECTION=std::stof(value);break;
        case 3: _DELTA_T=std::stof(value);break;
        case 4: {float p_error=std::stof(value); _POSITION_VAR=p_error*p_error; break;}
        case 5: {float v_error=std::stof(value); _VELOCITY_VAR=v_error*v_error; break;}
        case 6: {float z_error=std::stof(value); _MEAS_VAR=z_error*z_error; break;}
        case 7: {float x_error=std::stof(value); _STATE_VAR=x_error*x_error; break;}
        case 8: _CLUTTER_DENSITY=std::stof(value); break;
        case 9: _NEW_TARGET_DENSITY=std::stof(value); break;
        case 10: _TRACK_GATE_THRES=std::stof(value); break;
        case 11: _TRACK_SCORE_DEL_THRES=std::stof(value); break;
        case 12: _TRACK_SCORE_CONF_THRES=std::stof(value); break;
    }
}

}