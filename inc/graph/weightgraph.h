// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/07
// Author: Hongbin Zhou

#ifndef MHT_WEIGHT_GRAPH_H
#define MHT_WEIGHT_GRAPH_H

#include <set>

#include "log/log.h"
#include "graph/graph.h"

namespace mht_graph {

using std::set;

class weightedGraph: public Graph {

public:

    weightedGraph();

    ~weightedGraph();

    void addWeightedVertex(const int& vertex, const float& weight);

    //Maximum Weighted Independent Set of Graph
    static void getMWIS(weightedGraph& wgraph, vector<int>& optimals);

    static void bronKerbosh3(weightedGraph& wgraph);

    static void getNeighbors();

    static void degeneracyOrder(weightedGraph& wgraph, vector<int>& order);

private:

    map<int, float> _weights;


};

}

#endif