// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_MEAS_H
#define MHT_MEAS_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <memory>

#include <eigen3/Eigen/Eigen>

#include "log/log.h"
#include "meas/meas_param.h"
#include "common/random.h"

namespace mht_measurement {

using std::string;
using std::vector;

class Measurement {

public:
  
    Measurement();

    Measurement(const string& param_path);

    ~Measurement();

    void set_random(std::shared_ptr<mht_common::Random>& random);

    void load_parameters(const string& param_path);

    void generate_targets();

    void generate_noises();

    void generate_measures();

private:

    std::map<string, string> load_param_file(const string& param_path);

public:

private:

    std::shared_ptr<mht_common::Random> _random;

    MeasParams _meas_params;
    
};

}

#endif