// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#include "tracker/target.h"

namespace mht_tracker {

Target::Target(){
}

Target::Target(const Eigen::VectorXf& meas, const float& r, const float& p, 
               const float& d_gate, const vector<float>& q, const float& delta_t){

    auto dim = meas.size();
    
    initMatrix(dim);

    initParams(meas, r, p, d_gate, q, delta_t);

}

Target::~Target(){

}

void Target::initTrackScore(const float& p_d, const float& ts_del, const float& ts_conf,
                            const float& p_fa, const float& p_n, const float& volume){

    _log_p_d = log(p_d);
    _volume = volume;

    _track_score = log(p_n)-log(p_fa);
    _llr_miss = log(1-p_d)-log(1-p_fa);
    
    _llr_del_thres = log(ts_del);
    _llr_conf_thres = log(ts_conf);

    _log_beta_fa = log(p_fa/volume);
}

void Target::predictLLR(){

    predict();

}

void Target::updateLLR(const Eigen::VectorXf& meas){

    // if(update(meas)){
    //     float delat_LLR = _log_p_d - _log_beta_fa - meas.size()*0.5*log(2*PI) - \
    //                       0.5 * getMahDis2() - 0.5 * log(getDeterminS()) ;
    //     _track_score += delat_LLR;
    // }
    // else{
    //     _track_score = INT_MIN;
    // }   
}

void Target::missDetection(){
    
    _X = _X_pre;
    _track_score += _llr_miss;
}

float Target::getTrackScore(){
    return _track_score;
}

bool Target::isDead(){
    return _track_score <= _llr_del_thres;
}

bool Target::isConfirm(){
    return _track_score >= _llr_del_thres;
}

}