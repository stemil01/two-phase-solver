#include <iostream>
#include <vector>
#include "coordinates.hpp"
#include "moves.hpp"
#include "pruning_tables.hpp"
#include "search.hpp"
using namespace std;

int main()
{
    generate_moving_tables();
    generate_phase1_pruning_table();
    generate_phase2_pruning_tables();

    // testiranje pretrage
    int corner_orientation = 0, edge_orientation = 0, UDslice_edge_position = 0;
    int corner_permutation = 0, UD_edge_permutation = 0, UDslice_edge_permutation = 0;
    Edges cubie_edge_permutation[12];
    Edges moved[12];

    for (int i = 0; i < 12; i++)
        cubie_edge_permutation[i] = (Edges)i;

    cout << "Potezi za kocku: ";
    for (int i = 0; i < 20; i++)
    {
        int move = rand() % 18;
        print_move(move);

        corner_orientation = move_corner_orientation[corner_orientation][move];
        edge_orientation = move_edge_orientation[edge_orientation][move];
        UDslice_edge_position = move_UDslice_edge_position[UDslice_edge_position][move];

        corner_permutation = move_corner_permutation[corner_permutation][move];
        Corners temp[8];
        corner_permutation_to_cubie(corner_permutation, temp);

        int base_move = (move / 3) * 3;
        int rem_move = move % 3;
        for (int j = 0; j <= rem_move; j++)
        {
            for (int k = 0; k < 12; k++)
                moved[k] = cubie_edge_permutation[move_edge[base_move][k]];
            for (int k = 0; k < 12; k++)
                cubie_edge_permutation[k] = moved[k];
        }
    }
    cout << '\n';

    vector<int> v;
    test_phase1_search(corner_orientation, edge_orientation, UDslice_edge_position, &v);

    cout << "Resenje za prvu fazu bi trebalo da bude: ";
    for (int i = 0; i < v.size(); i++)
    {
        print_move(v[i]);

        corner_permutation = move_corner_permutation[corner_permutation][v[i]];
        int base_move = (v[i] / 3) * 3;
        int rem_move = v[i] % 3;
        for (int j = 0; j <= rem_move; j++)
        {
            for (int k = 0; k < 12; k++)
                moved[k] = cubie_edge_permutation[move_edge[base_move][k]];
            for (int k = 0; k < 12; k++)
                cubie_edge_permutation[k] = moved[k];
        }
    }
    cout << '\n';

    Corners temp[8];
    corner_permutation_to_cubie(corner_permutation, temp);

    Edges cubie_UD_edge_permutation[8], cubie_UDslice_edge_permutation[4];
    for (int i = 0; i < 8; i++)
        cubie_UD_edge_permutation[i] = cubie_edge_permutation[i];
    for (int i = 0; i < 4; i++)
        cubie_UDslice_edge_permutation[i] = cubie_edge_permutation[i + 8];
    cubie_to_UD_edge_permutation(cubie_UD_edge_permutation, &UD_edge_permutation);
    cubie_to_UDslice_edge_permutation(cubie_UDslice_edge_permutation, &UDslice_edge_permutation);
    
    test_phase2_search(corner_permutation, UD_edge_permutation, UDslice_edge_permutation);

    // CubieLevelCube cube;
    // input(&cube);
}
