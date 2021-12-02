// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/27
// Author: Hongbin Zhou

#ifndef MHT_MEAS_PARAM_H
#define MHT_MEAS_PARAM_H

#include "log/log.h"
#include "common/param.h"
#include <iostream>

namespace mht_measurement {

using std::string;

class MeasParams: public mht_common::Parameters {

public:
    
    MeasParams();

    MeasParams(const string& param_path);

    int get_sample_num();

protected:

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
    //EXPECT OF NOISE: default=1
    int _EXPECT_NOISE=2;
    //EXPECT OF NOISE: default=1
    float _MEASUREMENT_NOISE=3;
    //@todo: SENSOR POS

private:
    
    const static std::vector<string> _keys;

};



}

#endif