// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/27
// Author: Hongbin Zhou

#ifndef MHT_MEAS_H
#define MHT_MEAS_H

#include <map>
#include <string>
#include <vector>

#include "log/log.h"

namespace mht_measurement {

using std::string;

class MeasParams{

public:
    
    MeasParams();

    void set_params(const string& key, const string& value);

public:
    //SCENE DIMENSION: default=2 for x,y
    int _SCENE_DIMENSION=2;
    //SCENE TYPE: default Rectangle
    string _SCENE_TYPE="Rectangle";
    //SCNEN RANGE: unit(m)
    float _SCENE_RANGE=100;
    //SCNEN TARGET: default=3
    int _SCENE_TARGET=3;
    //TARGET MOTION: default=CV
    string _TARGET_MOTION="CV";
    //SAMPLE INTERVAL: default=0.1
    float _SAMPLE_INTERVAL=0.1;
    //TIME START: default=0
    float _TIME_START=0;
    //TIME START: default=0
    float _TIME_END=1;
    //TIME START: unit(m/s)
    float _INIT_SPEED_RANGE=10;
    //@todo: SENSOR POS

private:
    
    const static std::vector<string> _keys;
    std::map<string, int> _param_key_dict;

};



}

#endif