// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/30
// Author: Hongbin Zhou

#ifndef MHT_PARAM_H
#define MHT_PARAM_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "log/log.h"

#include "common/utils.h"

namespace mht_common {

using std::string;

class Parameters{

public:

    virtual void load_parameters(const string& param_path);

protected:

    virtual void init_key_dict(const std::vector<string>& keys);

    virtual void load_param_file(const string& param_path);

    virtual void set_params(const string& key, const string& value)=0;

protected:

    const static std::vector<string> _keys;

    std::map<string, string> _param_dict;
    std::map<string, int> _param_key_dict;

};

}

#endif