// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/26
// Author: Hongbin Zhou

#ifndef MHT_TARGET_H
#define MHT_TARGET_H

#include <cmath>

#include "log/log.h"
#include "tracker/kalman.h"
#include "climits"

namespace mht_tracker {

using std::log;

#define PI 3.141592653589793

class Target: public Kalman {

public:

    Target();

    Target(const Eigen::VectorXf& meas, const float& r, const float& p, 
           const float& d_gate, const vector<float>& q, const float& delta_t);
  
    ~Target();

    void initTrackScore(const float& p_d, const float& ts_del, const float& ts_conf,
                        const float& p_fa, const float& p_n, const float& volume);

    void predictLLR();

    void updateLLR(const Eigen::VectorXf& meas);

    void missDetection();

    float getTrackScore(); 

    bool isDead();

    bool isConfirm();

private:

    float _track_score;

    float _log_beta_fa, _log_p_d, _llr_del_thres, _llr_conf_thres, _llr_miss, _volume;

};

}

#endif