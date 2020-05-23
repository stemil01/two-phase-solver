#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>
#include <chrono>
using namespace std;

void phase1_search(int corner_orientation, int edge_orientation, int UDslice_edge_position, vector<int> *phase2_solution);

void dfs(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation, unsigned char current_depth, unsigned char depth, int prev, bool *solved, vector<int> *phase2_solution);
void phase2_search(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation, int limit, bool *solved, vector<int> *phase2_solution);
bool search(Cube cube, int limit, vector<int> *solution);

void random_moves_search(Cube cube, int current_depth, int depth, int prev, int *limit, vector<int> *prefix, chrono::steady_clock::time_point begin, int time_limit);
void improve_search(Cube cube, int time_limit);

#endif // SEARCH_HPP