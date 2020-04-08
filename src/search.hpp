#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>
using namespace std;

void test_phase1_search(int corner_orientation, int edge_orientation, int UDslice_edge_position, vector<int> *solution);

void dfs(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation, unsigned char current_depth, unsigned char depth, int prev, vector<int> *solution);
void test_phase2_search(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation);

#endif // SEARCH_HPP