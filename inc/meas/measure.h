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

class Measurement {

public:

    typedef vector<vector<Eigen::VectorXf>> seq_data;
  
    Measurement();

    Measurement(const string& param_path);

    Measurement(const string& param_path, const std::shared_ptr<mht_common::Random>& random);

    ~Measurement();

    void set_random(const std::shared_ptr<mht_common::Random>& random);

    void load_parameters(const string& param_path);

    void generate_noises(seq_data& noises_pos);

    void generate_targets(seq_data& targets_state);

    void generate_measures(seq_data& measures, seq_data& targets, seq_data& noises);

private:

    std::map<string, string> load_param_file(const string& param_path);

private:

    std::shared_ptr<mht_common::Random> _random;

    MeasParams _meas_params;
    
};

}

#endif