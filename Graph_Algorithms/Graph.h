// Student ID: 20274909

#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>
#include <cfloat>

using namespace std;

#ifndef Graph_h
#define Graph_h

class Graph {
public:
   struct Edge {
      int dst;
      float wt;
      Edge(int tgt = -1, float w = 0) : dst(tgt), wt(w) {}
      bool operator==(const Edge& that) const { return dst == that.dst && wt == that.wt; }
      bool operator!=(const Edge& that) const { return dst != that.dst || wt != that.wt; }
   };

protected:
   static double constexpr FLOOR = 1e-6;
   std::vector<std::vector<Edge>> _nodes;

public:

   Graph() {}

   size_t get_num_nodes() const { return _nodes.size(); }
   bool is_empty() const { return _nodes.empty(); }
   void clear() { _nodes.clear(); }
   void clear_edges(int src) { _nodes[src].clear(); }
   std::string to_string() const;

   Graph& add_edge(int src, int tgt, float wt, bool replace = true);
   float find_edge_weight(int src, int tgt) const;

   friend class Gx;
   friend class Tests; // Don't remove this line.
};

#endif