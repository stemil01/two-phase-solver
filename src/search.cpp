#include <iostream>
#include <vector>
#include "moves.hpp"
#include "pruning_tables.hpp"
using namespace std;

void phase1_search(int corner_orientation, int edge_orientation, int UDslice_edge_position, vector<int> *phase2_solution)
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

                (*phase2_solution).push_back(move);
            }
        }
    }
    cout << '\n';
}

void dfs(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation, unsigned char current_depth, unsigned char depth, int prev, vector<int> *phase2_solution)
{
    if (current_depth == depth)
    {
        if (corner_permutation == 0 && UD_edge_permutation == 0 && UDslice_edge_permutation == 0)
            (*phase2_solution).push_back(prev);
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
                        if ((*phase2_solution).empty())
                        {
                            int moved_corner_permutation = move_corner_permutation[corner_permutation][move];
                            int moved_UD_edge_permutation = move_UD_edge_permutation[UD_edge_permutation][move];
                            int moved_UDslice_edge_permutation = move_UDslice_edge_permutation[UDslice_edge_permutation][move];

                            dfs(moved_corner_permutation, moved_UD_edge_permutation, moved_UDslice_edge_permutation, current_depth + 1, depth, move, phase2_solution);
                            if (!(*phase2_solution).empty())
                                (*phase2_solution).push_back(prev);
                        }
                    }
        }
    }
}

void phase2_search(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation, vector<int> *phase2_solution)
{
    int limit = 18;
    unsigned char depth = get_phase2_pruning_value(corner_permutation, UD_edge_permutation, UDslice_edge_permutation);
    while (depth <= limit && (*phase2_solution).empty())
    {
        dfs(corner_permutation, UD_edge_permutation, UDslice_edge_permutation, 0, depth, -1, phase2_solution);
        depth++;
    }
}

void search(Cube cube, vector<int> *solution)
{
    // ovde treba eksperimentisati sa potezima na pocetku
    
    vector<int> phase1_solution;
    phase1_search(cube.corner_orientation, cube.edge_orientation, cube.UDslice_edge_position, &phase1_solution);


    Edges moved[12];
    for (int i = 0; i < phase1_solution.size(); i++)
    {
        cube.corner_permutation = move_corner_permutation[cube.corner_permutation][phase1_solution[i]];
        int base_move = (phase1_solution[i] / 3) * 3;
        int rem_move = phase1_solution[i] % 3;
        for (int j = 0; j <= rem_move; j++)
        {
            for (int k = 0; k < 12; k++)
                moved[k] = cube.cubie_edge_permutation[move_edge[base_move][k]];
            for (int k = 0; k < 12; k++)
                cube.cubie_edge_permutation[k] = moved[k];
        }
    }

    int UD_edge_permutation, UDslice_edge_permutation;
    Edges cubie_UD_edge_permutation[8], cubie_UDslice_edge_permutation[4];
    for (int i = 0; i < 8; i++)
        cubie_UD_edge_permutation[i] = cube.cubie_edge_permutation[i];
    for (int i = 0; i < 4; i++)
        cubie_UDslice_edge_permutation[i] = cube.cubie_edge_permutation[i + 8];
    cubie_to_UD_edge_permutation(cubie_UD_edge_permutation, &UD_edge_permutation);
    cubie_to_UDslice_edge_permutation(cubie_UDslice_edge_permutation, &UDslice_edge_permutation);

    vector<int> phase2_solution;
    phase2_search(cube.corner_permutation, UD_edge_permutation, UDslice_edge_permutation, &phase2_solution);

    for (int i = 0; i < phase1_solution.size(); i++)
        (*solution).push_back(phase1_solution[i]);
    for (int i = phase2_solution.size() - 2; i >= 0; i--)
        (*solution).push_back(phase2_solution[i]);
}
