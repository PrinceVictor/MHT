// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_KALMAN_H
#define MHT_KALMAN_H

#include <eigen3/Eigen/Eigen>

#include "log/log.h"

namespace mht_tracker {


class Kalman {

public:
    Kalman();
    // Kalman(const int dim);

    ~Kalman();

    void predict();

    void update(const Eigen::VectorXf& meas);

    Eigen::VectorXf innovation(const Eigen::VectorXf& meas);
  
private:

    Eigen::VectorXf _X_est, _X_pre;

    Eigen::MatrixXf _Q, _R, _covarince_P;

    Eigen::MatrixXf _state_trans_mat, _meas_mat;

    float _K;



};

}

#endif