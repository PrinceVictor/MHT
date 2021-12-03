// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/11/27
// Author: Hongbin Zhou

#include "common/utils.h"

namespace mht_common {

std::vector<std::string> strSplit(const std::string& input_str,  const std::string& match_str=" "){
    std::vector<std::string> result;
    std::string::size_type left=0, right=0;
    right = input_str.find(match_str, left);

    while(right != std::string::npos){
        result.emplace_back(input_str.substr(left, right - left));
        left = right+match_str.size();
        right = input_str.find(match_str, left);
    }
    if(left != input_str.size()){
        result.emplace_back(input_str.substr(left));
    }
    return result;
}

}