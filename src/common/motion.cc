// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/29
// Author: Hongbin Zhou

#include "common/motion.h"

namespace mht_common {

std::map<int, Eigen::MatrixXf> Motion::_cv_mat_dict;

const Eigen::MatrixXf& Motion::CV(const int dim, const float delta_t){

    if(Motion::_cv_mat_dict.count(dim) == 0){
        
        _cv_mat_dict[dim] = Eigen::MatrixXf::Identity(dim*2, dim*2);
    }
    auto& cv_mat = _cv_mat_dict[dim];

    for(int i = 0; i < dim; i++){
        cv_mat(i, i+dim) = delta_t;
    }

    return cv_mat;
}

}