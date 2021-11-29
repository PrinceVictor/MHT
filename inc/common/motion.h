// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/29
// Author: Hongbin Zhou

#ifndef MHT_MOTION_H
#define MHT_MOTION_H

#include "map"

#include <eigen3/Eigen/Eigen>

#include "log/log.h"

namespace mht_common {

class Motion {

public:

    Motion();

    const static Eigen::MatrixXf& CV(const int dim=2, const float delta_t=0.1);

    // Eigen::MatrixXf CA();

    // Eigen::MatrixXf CT();

    // Eigen::MatrixXf ST();

private:

    static std::map<int, Eigen::MatrixXf> _cv_mat_dict;

};

}


#endif