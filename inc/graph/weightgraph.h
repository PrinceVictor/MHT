// Copyright 2021 by Hongbin Zhou
// Created by Hongbin Zhou on 2021/12/07
// Author: Hongbin Zhou

#ifndef MHT_WEIGHT_GRAPH_H
#define MHT_WEIGHT_GRAPH_H

#include <set>
#include <algorithm>

#include "log/log.h"
#include "graph/graph.h"

#include "common/random.h"

namespace mht_graph {

using std::set;

class weightedGraph: public Graph {

public:

    weightedGraph();

    ~weightedGraph();

    void addWeightedVertex(const int& vertex, const float& weight);

    //Maximum Weighted Independent Set of Graph
    static void getMWIS(weightedGraph& wgraph, vector<int>& result);

    static void bronKerbosh3(weightedGraph& wgraph, vector<int>& result);

    static void bronKerbosh2(const set<int>& R, set<int> P, set<int> X, 
                             const vector<vector<int>>& g, vector<int>& result);

    static void getNeighbors(const int& v, const vector<vector<int>>& g, set<int>& n);

    static void degeneracyOrder(const vector<vector<int>>& g, vector<int>& order);

private:

    map<int, float> _weights;


};

set<int> operator - (const set<int>& a, const set<int>& b);
set<int> operator | (const set<int>& a, const set<int>& b);
set<int> operator & (const set<int>& a, const set<int>& b);

}

#endif