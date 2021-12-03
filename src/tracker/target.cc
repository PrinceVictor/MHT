// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "tracker/target.h"

namespace mht_tracker {

Target::Target(){
}

Target::Target(const Eigen::VectorXf& meas, const float& r, const float& p, 
               const vector<float>& q, const float& delta_t){

    auto dim = meas.size();
    
    initMatrix(dim);

    initParams(meas, r, p, q, delta_t);

}

Target::~Target(){

}

float Target::likeLihood(){

    
}

}