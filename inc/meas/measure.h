// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_MEAS_H
#define MHT_MEAS_H

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
#include "meas/measparam.h"

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

    void generateMeasures();

    const std::map<float, vector<Eigen::VectorXf>>& get_measurements();

private:

    void generateNoises();

    void generateTarget();

private:

    seq_data _targets, _noises;

    std::map<float, vector<Eigen::VectorXf>> _measures;

    MeasParams _params;
    
};

}

#endif