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
    
    _X_pre = _state_trans_mat * _X_est;
    _covarince_P = _state_trans_mat*_covarince_P*_state_trans_mat + _Q;

}

void Kalman::update(const Eigen::VectorXf& meas){
   
   auto inv = innovation(meas);
}

Eigen::VectorXf Kalman::innovation(const Eigen::VectorXf& meas){

    return meas - _meas_mat*_X_pre;
}

}