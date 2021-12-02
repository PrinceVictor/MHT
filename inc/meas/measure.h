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
#include <numeric>

#include <eigen3/Eigen/Eigen>

#include "log/log.h"
#include "common/random.h"
#include "common/motion.h"
#include "meas/meas_param.h"

namespace mht_measurement {

using std::string;
using std::vector;
using mht_common::Random;

class Measurement {

public:

    typedef vector<vector<Eigen::VectorXf>> seq_data;
  
    Measurement();

    Measurement(const string& param_path);

    Measurement(const string& param_path, const std::shared_ptr<mht_common::Random>& random);

    ~Measurement();

    void generate_measures();

    const std::map<float, vector<Eigen::VectorXf>>& get_measurements();

private:

    void generate_noises();

    void generate_targets();

    std::map<string, string> load_param_file(const string& param_path);

private:

    seq_data _targets, _noises;

    std::map<float, vector<Eigen::VectorXf>> _measures;

    MeasParams _params;
    
};

}

#endif