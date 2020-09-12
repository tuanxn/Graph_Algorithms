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

//int main()
//{
//   Graph test = Graph();
//   test.add_edge(0, 0, 0.f, false);
//
//   cout << test.to_string();
//
//   //cout << test.find_edge_weight(0, 1);
//
//
//}

Graph& Graph::add_edge(int src, int tgt, float wt, bool replace) {
   if ( src < 0 ||  tgt < 0) {
      return *this;
   }

   int max_num = max(src, tgt);
   max_num++;

   if (signed(_nodes.size()) < max_num)
      _nodes.resize(max_num);

   if (src == tgt)
      return *this;

   bool found = false;

   for (int i = 0; i < (signed)_nodes[src].size(); i++) {
      if (_nodes[src][i].dst == tgt) {
         found = true;
         if (replace) {
            _nodes[src][i].wt = wt;
         }
         else {
            _nodes[src][i].wt += wt;
         }
         break;
      }
   }

   if (!found)
      _nodes[src].push_back(Edge(tgt, wt));

   return *this;
}

float Graph::find_edge_weight(int src, int tgt) const {
   if (src >= (signed)get_num_nodes() || src < 0 || tgt >= (signed)get_num_nodes() || tgt < 0)
      return Graph::FLOOR;

   for (int i = 0; i < (signed)_nodes[src].size(); i++) {
      if (_nodes[src][i].dst == tgt)
         return _nodes[src][i].wt;
   }

   return Graph::FLOOR;
}

string Graph::to_string() const {
   string output = "# Graph - " + std::to_string(_nodes.size()) + " nodes.\n";
   output += "# Edge lists:\n";
   for (int i = 0; i < (signed)get_num_nodes(); i++) {
      if (_nodes[i].empty()) {
         continue;
      }
      output += std::to_string(i) + " : ";
      for (int j = 0; j < (signed)_nodes[i].size(); j++) {
         stringstream ss;
         ss << _nodes[i][j].wt;
         output += "(" + std::to_string(_nodes[i][j].dst) + "," + ss.str() + ") ";
      }
      output += "\n";
   }
   output += "# End of Graph\n";
   return output;
}

