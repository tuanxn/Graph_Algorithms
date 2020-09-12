// Student ID: 20274909

#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <iostream>
#include "Graph_Algorithms.h"
#include <queue>
#include <cmath>
#include <climits>
#include <cfloat>

using namespace std;

//int main()
//{
//
//
//
//   Graph g = Graph();
//   g.add_edge(0, 3, 3);
//   g.add_edge(0, 2, 2);
//   g.add_edge(0, 6, 6);
//   g.add_edge(0, 4, 4);
//   g.add_edge(0, 10, 10);
//   g.add_edge(2, 10, 210);
//   g.add_edge(2, 4, 203);
//   g.add_edge(3, 7, 307);
//   g.add_edge(3, 8, 308);
//   g.add_edge(3, 2, 302);
//   g.add_edge(4, 9, 409);
//   g.add_edge(4, 5, 405);
//   g.add_edge(5, 8, 508);
//   g.add_edge(6, 10, 610);
//   g.add_edge(7, 4, 704);
//
//   g.add_edge(7, 3, 111);
//
//   g.add_edge(8, 9, 1618);
//   g.add_edge(9, 7, 907);
//   g.add_edge(9, 1, 901);
//   g.add_edge(10, 1, 1001);
//   g.add_edge(10, 9, 1009);
//   g.add_edge(10, 7, 1007);
//
//   // max flow is 713
//
//
//   Gx test = Gx();
//
//   cout << g.to_string();
//
//   vector<int> path;
//
//   //cout << Gx::get_capacity(g, path);
//
//   cout << Gx::get_max_flow(g, 3, 8);
//}

bool Gx::_is_cyclic(const Graph& g, size_t node, std::vector<bool> seen, std::vector<bool>& cycle_free) {
   if (seen[node])
      return true;

   if (cycle_free[node])
      return false;

   for (size_t i = 0; i < g._nodes[node].size(); i++) {
      seen[node] = true;
      if (_is_cyclic(g, g._nodes[node][i].dst, seen, cycle_free))
         return true;
   }

   return false;
}

bool Gx::is_cyclic(const Graph& g) {
   int num_nodes = g.get_num_nodes();
   vector<bool> cycle_free(num_nodes, false);
   for (int i = 0; i < num_nodes; i++) {
      vector<bool> seen(num_nodes, false);
      if (_is_cyclic(g, i, seen, cycle_free))
         return true;
      cycle_free[i] = true;
   }
   return false;
}

bool Gx::prune_unreachables(Graph& g, int src) {
   int num_nodes = g._nodes.size();
   if (src >= num_nodes || src < 0) {
      g.clear();
      return false;
   }

   vector<bool> reachable(num_nodes, false);

   _get_reachable(g, src, reachable);

   for (int i = 0; i < num_nodes; i++) {
      if (!reachable[i])
         g.clear_edges(i);
   }

   return true;
}

void Gx::_get_reachable(const Graph& g, int src, vector<bool>& reachable) {
   reachable[src] = true;

   for (size_t i = 0; i < g._nodes[src].size(); i++) {
      if (!reachable[g._nodes[src][i].dst])
         _get_reachable(g, g._nodes[src][i].dst, reachable);
   }
}

size_t Gx::get_shortest_unweighted_path(const Graph& g, int src, int dst, std::vector<int>& path) {
   int num_nodes = g.get_num_nodes();
   path.clear();

   if (src >= num_nodes || src < 0 || dst >= num_nodes || dst < 0) {
      return string::npos;
   }else if (src == dst) {
      path.resize(1);
      path[0] = src;
      return path.size();
   }

   queue<int> to_process;
   vector<bool> seen(num_nodes, false);
   vector<int> path_length(num_nodes), parents(num_nodes);

   to_process.push(src);
   seen[src] = true;
   parents[src] = -1;

   while (!to_process.empty()) {
      int next = to_process.front();
      to_process.pop();
      for (Graph::Edge current : g._nodes[next]) {
         if (!seen[current.dst]) {
            seen[current.dst] = true;
            to_process.push(current.dst);
            path_length[current.dst] = path_length[next] + 1;
            parents[current.dst] = next;
            if (current.dst == dst)
               break;
         }
      }
   }

   if (!seen[dst]) {
      return string::npos;
   }

   for (int i = dst; i != -1; i = parents[i])
      path.insert(path.begin(), i);
   return path.size();

}

size_t Gx::get_shortest_weighted_path(const Graph& g, int src, int dst, std::vector<int>& path) {
   int num_nodes = g.get_num_nodes();
   path.clear();

   if (src >= num_nodes || src < 0 || dst >= num_nodes || dst < 0) {
      return string::npos;
   }
   else if (src == dst) {
      path.resize(1);
      path[0] = src;
      return path.size();
   }

   // initialize set of vertices to hold shorted path length and predecessor
   vector<NW> vertices;
   for (int i = 0; i < num_nodes; i++) {
      vertices.push_back(NW(i, -1, 999999999999.f));
   }

   // priority queue to hold next vertice to process
   priority_queue<NW, vector<NW>, Gx::compare > to_process;

   // start with first source vertice
   to_process.push(NW(src, src, 0));

   while (!to_process.empty()) {
      NW next_shortest = to_process.top();
      to_process.pop();

      if (vertices[next_shortest.node].weight < next_shortest.weight)
         continue;

      for (Graph::Edge current_edge : g._nodes[next_shortest.node]) {
         if (vertices[current_edge.dst].weight > (next_shortest.weight + current_edge.wt)) {
            vertices[current_edge.dst].weight = next_shortest.weight + current_edge.wt;
            vertices[current_edge.dst].pred = next_shortest.node;
            to_process.push(NW(current_edge.dst, next_shortest.node, next_shortest.weight + current_edge.wt));
         }
      }
   }

   if (vertices[dst].pred == -1) {
      return string::npos;
   }

   for (int i = dst; i != src; i = vertices[i].pred)
      path.insert(path.begin(), i);
   path.insert(path.begin(), src);
   return path.size();

}

float Gx::_get_capacity_of_this_path(const Graph& g, const std::vector<int>& path) {
   if (path.empty() || path.size() == 1)
      return 0.f;

   float capacity = 9999999999.f;
   for (int i = 0; i < signed(path.size() - 1); i++) {
      for (int j = 0; j < signed(g._nodes[path[i]].size()); j++)
         if (g._nodes[path[i]][j].dst == path[i + 1] && capacity > g._nodes[path[i]][j].wt) {
            capacity = g._nodes[path[i]][j].wt;
            break;
         }
   }
   return capacity;
}

float Gx::get_capacity(const Graph& g, const std::vector<int>& path) {
   return _get_capacity_of_this_path(g, path);
}

float Gx::_get_max_capacity_path(const Graph& g, int src, int dst, std::vector<int>& path) {
   int num_nodes = g.get_num_nodes();
   path.clear();

   if (src >= num_nodes || src < 0 || dst >= num_nodes || dst < 0) {
      return 0.f;
   }
   else if (src == dst) {
      path.resize(1);
      path[0] = src;
      return 0.f;
   }

   // initialize set of vertices to hold longest path length and predecessor
   vector<NW> vertices;
   for (int i = 0; i < num_nodes; i++) {
      vertices.push_back(NW(i, -1, -1.f));
   }

   // priority queue to hold next vertice to process
   priority_queue<NW, vector<NW>, Gx::max_compare > to_process;

   // start with first source vertice
   to_process.push(NW(src, src, 0));

   bool found = false;

   while (!to_process.empty()) {
      NW next_shortest = to_process.top();
      to_process.pop();

      for (Graph::Edge current_edge : g._nodes[next_shortest.node]) {

         if (vertices[current_edge.dst].pred != -1)
            continue;

         vertices[current_edge.dst].weight = next_shortest.weight + current_edge.wt;
         vertices[current_edge.dst].pred = next_shortest.node;
         to_process.push(NW(current_edge.dst, next_shortest.node, next_shortest.weight + current_edge.wt));

         if (current_edge.dst == dst) {
            found = true;
            break;
         }
      }

      if (found)
         break;
   }

   if (vertices[dst].pred == -1) {
      return string::npos;
   }

   for (int i = dst; i != src; i = vertices[i].pred)
      path.insert(path.begin(), i);
   path.insert(path.begin(), src);

   return Gx::_get_capacity_of_this_path(g, path);

}

float Gx::get_max_flow(const Graph& g, int src, int dst) {
   Graph copy = g;
   float total = 0.f;
   vector<int> path;
   while (true) {
      float flow = _get_max_capacity_path(copy, src, dst, path);
      if (flow == string::npos) {
         break;
      }
      total += flow;
      for (size_t i = 0; i < path.size() - 1; i++) {
         for (size_t j = 0; j < copy._nodes[path[i]].size(); j++) {
            if (copy._nodes[path[i]][j].dst == path[i + 1]) {
               copy.add_edge(path[i + 1], path[i], copy._nodes[path[i]][j].wt, false);
               
               copy._nodes[path[i]][j].wt -= flow;
               if (!copy._nodes[path[i]][j].wt)
                  copy._nodes[path[i]].erase(copy._nodes[path[i]].begin() + j);
            }
         }
      }
   }
   return total;
}
