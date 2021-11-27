// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_MEAS_H
#define MHT_MEAS_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include "log/log.h"
#include "meas/meas_param.h"

namespace mht_measurement {

using std::string;

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