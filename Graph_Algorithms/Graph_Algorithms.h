// Student ID: 20274909

#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <iostream>
#include "Graph.h"
#include <cmath>
#include <climits>
#include <cfloat>

using namespace std;

#ifndef Graph_Algorithms_h
#define Graph_Algorithms_h

class Gx {
private:
   struct NW { // package three co-used qtys
      int node, pred;
      float weight;
      NW(int n, int m, float wt) : node(n), pred(m), weight(wt) {}
      bool operator<(const NW& that) const { return this->weight > that.weight; }
      bool operator>(const NW& that) const { return this->weight < that.weight; }
   };

   struct compare
   {
      bool operator()(const NW& a, const NW& b) {
         return a.weight > b.weight;
      }
   };

   struct max_compare
   {
      bool operator()(const NW& a, const NW& b) {
         return a.weight < b.weight;
      }
   };

   static float _get_capacity_of_this_path(const Graph& g, const std::vector<int>& path);
   static float _get_max_capacity_path(const Graph& g, int src, int dst, std::vector<int>& path);
   static bool _is_cyclic(const Graph& g, size_t node, std::vector<bool> seen, std::vector<bool>& cycle_free);
   static void _get_reachable(const Graph& g, int src, vector<bool>& reachable);
  

public:
   static bool is_cyclic(const Graph& g);
   static bool prune_unreachables(Graph& g, int src);
   static size_t get_shortest_unweighted_path(const Graph& g, int src, int dst, std::vector<int>& path);
   static size_t get_shortest_weighted_path(const Graph& g, int src, int dst, std::vector<int>& path);

   static float get_max_flow(const Graph& g, int src, int dst);

   static float get_capacity(const Graph& g, const std::vector<int>& path);

   friend class Tests; // Don't remove
};

#endif