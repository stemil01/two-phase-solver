#include <iostream>
#include <vector>
#include "moves.hpp"
#include "pruning_tables.hpp"
using namespace std;

void test_phase1_search(int corner_orientation, int edge_orientation, int UDslice_edge_position, vector<int> *solution)
{
    int depth = get_phase1_pruning_value(get_phase1_state(corner_orientation, edge_orientation, UDslice_edge_position));
    while (!(corner_orientation == 0 && edge_orientation == 0 && UDslice_edge_position == 0))
    {
        bool found = false;

        int corner_temp[8];
        corner_orientation_to_cubie(corner_orientation, corner_temp);
        int edge_temp[12];
        edge_orientation_to_cubie(edge_orientation, edge_temp);
        bool UDslice_temp[12];
        UDslice_edge_position_to_cubie(UDslice_edge_position, UDslice_temp);

        for (int move = 0; move < 18 && !found; move++)
        {
            int moved_corner_orientation = move_corner_orientation[corner_orientation][move];
            int moved_edge_orientation = move_edge_orientation[edge_orientation][move];
            int moved_UDslice_edge_position = move_UDslice_edge_position[UDslice_edge_position][move];

            int moved_depth = get_phase1_pruning_value(get_phase1_state(moved_corner_orientation, moved_edge_orientation, moved_UDslice_edge_position));
            if (moved_depth == (depth + 2) % 3) // ovo je kao (depth - 1) % 3, ali -1 % 3 je -1 u c++-u iz nekog razloga
            {
                found = true;
                corner_orientation = moved_corner_orientation;
                edge_orientation = moved_edge_orientation;
                UDslice_edge_position = moved_UDslice_edge_position;
                depth = moved_depth;

                (*solution).push_back(move);
            }
        }
    }
    cout << '\n';
}

void dfs(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation, unsigned char current_depth, unsigned char depth, int prev, vector<int> *solution)
{
    if (current_depth == depth)
    {
        if (corner_permutation == 0 && UD_edge_permutation == 0 && UDslice_edge_permutation == 0)
            (*solution).push_back(prev);
    }
    else 
    {
        unsigned char heuristic = get_phase2_pruning_value(corner_permutation, UD_edge_permutation, UDslice_edge_permutation);
        if (current_depth +  heuristic <= depth)
        {
            for (int move = 0; move < 18; move++)
                if (move % 3 == 1 || move >= 12) // potezi faze 2
                    if ((prev < 12 && move != prev) || (prev < 15 && move != 12 && move != 13 && move != 14) || (move != 15 && move != 16 && move != 17)) // za prethodni potez
                    {
                        if ((*solution).empty())
                        {
                            int moved_corner_permutation = move_corner_permutation[corner_permutation][move];
                            int moved_UD_edge_permutation = move_UD_edge_permutation[UD_edge_permutation][move];
                            int moved_UDslice_edge_permutation = move_UDslice_edge_permutation[UDslice_edge_permutation][move];

                            dfs(moved_corner_permutation, moved_UD_edge_permutation, moved_UDslice_edge_permutation, current_depth + 1, depth, move, solution);
                            if (!(*solution).empty())
                                (*solution).push_back(move);
                        }
                    }
        }
    }
}

void test_phase2_search(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation)
{
    int limit = 18;
    unsigned char depth = get_phase2_pruning_value(corner_permutation, UD_edge_permutation, UDslice_edge_permutation);
    vector<int> solution;
    while (depth <= limit && solution.empty())
    {
        bool goon = true;
        char answer;
        cout << "Trenutno se pretrazuje dubina " << (int)depth << "; Da li zelite da nastavite? [Y/n] ";
        cin >> answer;
        if (answer == 'N' || answer == 'n')
            goon = false;
        
        if (goon)
        {
            dfs(corner_permutation, UD_edge_permutation, UDslice_edge_permutation, 0, depth, -1, &solution);
            depth++;
        }
    }

    cout << "Resenje druge faze bi trebalo da bude: ";
    for (int i = solution.size() - 1; i > 0; i--)
        print_move(solution[i]);
    cout << '\n';
}
