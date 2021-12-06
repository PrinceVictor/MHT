// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_KALMAN_H
#define MHT_KALMAN_H

#include <vector>

#include <eigen3/Eigen/Eigen>

#include "log/log.h"
#include "common/motion.h"

namespace mht_tracker {

using std::vector;

class Kalman {

public:
    Kalman();

    ~Kalman();

    virtual void initMatrix(const int& dim);
    
    virtual void initParams(const Eigen::VectorXf& meas, const float& r, const float& p, 
                            const float& d_gate, const vector<float>& q, const float& delta_t);

    virtual void predict();

    virtual bool update(const Eigen::VectorXf& meas);

    virtual float getMahDis2();

    virtual float getDeterminS();

    Eigen::VectorXf innovation(const Eigen::VectorXf& meas);

    Eigen::MatrixXf residualCovarianceMat();
  
private:

public:

    Eigen::VectorXf _X, _X_pre;

    Eigen::MatrixXf _Q, _R, _P;

    Eigen::MatrixXf _F, _H;

    float _d_gate, _d2, _det_S;
};

}

#endif