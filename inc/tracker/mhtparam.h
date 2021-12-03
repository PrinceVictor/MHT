// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/30
// Author: Hongbin Zhou

#ifndef MHT_TRACK_PARAM_H
#define MHT_TRACK_PARAM_H

#include "log/log.h"
#include "common/param.h"

namespace mht_tracker {

using std::string;

class MHTParams: public mht_common::Parameters{

public:
    MHTParams();

    MHTParams(const string& param_path);

protected:

    void setParams(const string& key, const string& value);

public:
    //SCENE DIMENSION: default=2 for x,y
    int _SCENE_DIMENSION=2;
    //PROBABILITY of DETECTION
    float _P_DETECTION=0.9;


private:
    
    const static std::vector<string> _keys;

};


}


#endif