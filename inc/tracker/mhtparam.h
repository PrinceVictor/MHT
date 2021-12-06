// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/30
// Author: Hongbin Zhou

#ifndef MHT_TRACK_PARAM_H
#define MHT_TRACK_PARAM_H

#include "log/log.h"
#include "common/param.h"

namespace mht_tracker {

using std::string;

class MHTParams: public mht_common::Parameters{

public:
    MHTParams();

    MHTParams(const string& param_path);

protected:

    void setParams(const string& key, const string& value);

public:
    //SCENE DIMENSION: default=2 for x,y
    int _SCENE_DIMENSION=2;
    //PRUN SCAN
    int N_SCAN=2;
    //PROBABILITY of DETECTION
    float _P_DETECTION=0.9;
    //TIME INTERVAL
    float _DELTA_T=0.1;
    //POS VARIANCE
    float _POSITION_VAR=1;
    //SPEED VARIANCE
    float _VELOCITY_VAR=3;
    //MEASUREMENT NOISE
    float _MEAS_VAR=5;
    //STATE ERROR VARIANCE
    float _STATE_VAR=10;
    //CLUTTER DENSITY
    float _CLUTTER_DENSITY=1;
    //NEW TARGET DENSITY
    float _NEW_TARGET_DENSITY=0.15;
    //TRACK GATE THRESHOLD
    float _TRACK_GATE_THRES=0.5;
    //TRACK SCORE DELETE THRESHOLD
    float _TRACK_SCORE_DEL_THRES=0.05;
    //TRACK SCORE CONFIRM THRESHOLD
    float _TRACK_SCORE_CONF_THRES=0.25;
    //SCENE VOLUME
    float _SCENE_VOLUME=100;



private:
    
    const static std::vector<string> _keys;

};


}


#endif