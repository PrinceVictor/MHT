// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "tracker/kalman.h"

namespace mht_tracker {

Kalman::Kalman(){
}

Kalman::~Kalman(){
}

void Kalman::initMatrix(const int& dim){
    
    _X = Eigen::VectorXf::Zero(dim*2);
    _F = Eigen::MatrixXf::Identity(dim*2, dim*2);
    _H = Eigen::MatrixXf::Identity(dim, dim*2);
    _P = Eigen::MatrixXf::Identity(dim*2, dim*2);
    _Q = Eigen::MatrixXf::Identity(dim*2, dim*2);
    _R = Eigen::MatrixXf::Identity(dim, dim);
}

void Kalman::initParams(const float& r, const float& p, const float& pos_q, const float& velo_q){

    _P = _P*p;
    _R = _R*r;
    int dim = _R.rows();
    _Q.topLeftCorner(dim, dim) = _Q.topLeftCorner(dim, dim)*pos_q;
    _Q.bottomRightCorner(dim, dim) = _Q.bottomRightCorner(dim, dim)*velo_q;

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