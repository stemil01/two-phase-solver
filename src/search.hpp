#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>
using namespace std;

void phase1_search(int corner_orientation, int edge_orientation, int UDslice_edge_position, vector<int> *phase2_solution);

void dfs(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation, unsigned char current_depth, unsigned char depth, int prev, vector<int> *solution);
void phase2_search(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation, vector<int> *phase2_solution);
void search(Cube cube, vector<int> *solution);

#endif // SEARCH_HPP