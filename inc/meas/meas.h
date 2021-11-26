// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_MEAS_H
#define MHT_MEAS_H

#include "log/log.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

namespace mht_measurement {

using std::string;

class MeasParams{

public:
    void set_params(const string& key, const string& value);

public:
    //SCENE DIMENSION: default=2 for x,y
    int SCENE_DIMENSION=2;
    //SCENE TYPE: default Rectangle
    string SCENE_TYPE="Rectangle";
    //SCNEN RANGE: unit/m
    float SCENE_RANGE=100;
    //@todo: SENSOR POS
private:

};

class Measurement {

public:
  
    Measurement();

    Measurement(const string& param_path);

    ~Measurement();

    void load_parameters(const string& param_path);

private:

    std::map<string, string> load_param_file(const string& param_path);

    MeasParams _meas_params;
    

};

}

#endif