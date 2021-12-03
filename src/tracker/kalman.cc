// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "tracker/kalman.h"

namespace mht_tracker {

Kalman::Kalman(){

}

Kalman::~Kalman(){

}

void Kalman::predict(){
    
    _X = _F * _X;
    _P = _F*_P*_F.transpose() + _Q;
}

void Kalman::update(const Eigen::VectorXf& meas){
    
    auto y_tilde = innovation(meas);
    auto S = residualCovarianceMat();

    auto K = _P*_H.transpose()*S.inverse();
    _X = _X + K*y_tilde;
    _P = _P - K*S*K.transpose();
}

Eigen::VectorXf Kalman::innovation(const Eigen::VectorXf& meas){

    return meas - _H*_X;
}

Eigen::MatrixXf Kalman::residualCovarianceMat(){

    return _H* _P * _H.transpose() + _R;
}

}