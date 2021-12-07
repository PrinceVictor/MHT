// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/07
// Author: Hongbin Zhou

#include "graph/weightgraph.h"

namespace mht_graph {

weightedGraph::weightedGraph(){}

weightedGraph::~weightedGraph(){}

void weightedGraph::addWeightedVertex(const int& vertex, const float& weight){

    addVertex(vertex);
    _weights[vertex] = weight;
}

void weightedGraph::getMWIS(weightedGraph& wgraph, vector<int>& optimals){

}

}