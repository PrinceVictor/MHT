// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/30
// Author: Hongbin Zhou

#include "common/param.h"

namespace mht_common {

const std::vector<string> Parameters::_keys;

void Parameters::initKeyDict(const std::vector<string>& keys){

    for(int i=0; i<keys.size(); i++){
        _param_key_dict[keys[i]] = i;
        // std::cout<<keys[i]<<"="<<i<<std::endl;
    }
}

void Parameters::loadParameters(const string& param_path){

    loadParamFile(param_path);

    if(_param_dict.size()){
        for(auto it=_param_dict.begin(); it!=_param_dict.end(); it++){
            
            setParams(it->first, it->second);
        }
    }
}

void Parameters::loadParamFile(const string& param_path){

    LOG_INFO("Loading Parameters from {}", param_path);
    
    std::fstream param_stream(param_path, std::fstream::in);
    if(!param_stream.is_open()){
        throw "Open parameter file failed!";
    }

    string params;
    while(param_stream.good()){

        std::getline(param_stream, params);
        if(params.size() == 0 || (params[0] == '/' && params[1] == '/')) continue;

        auto key_value = strSplit(params, "=");
        _param_dict[key_value[0]] = key_value[1];

        // for(auto it: key_value) std::cout<< it <<'\t';
        // std::cout<<std::endl;
    }
    param_stream.close();
}

}