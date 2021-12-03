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

    ~Kalman();

    virtual void initMatrix(const int& dim);
    
    virtual void initParams(const float& r, const float& p, const float& pos_q, const float& velo_q);

    virtual void predict();

    virtual void update(const Eigen::VectorXf& meas);

    Eigen::VectorXf innovation(const Eigen::VectorXf& meas);

    Eigen::MatrixXf residualCovarianceMat();
  
private:

public:

    Eigen::VectorXf _X;

    Eigen::MatrixXf _Q, _R, _P;

    Eigen::MatrixXf _F, _H;

};

}

#endif