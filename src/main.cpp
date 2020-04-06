#include <iostream>
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

    // int corner_orientation = 0, edge_orientation = 0, UDslice_edge_position = 0;
    // cout << "Potezi za kocku: ";
    // for (int i = 0; i < 20; i++)
    // {
    //     int move;
    //     cin >> move;

    //     corner_orientation = move_corner_orientation[corner_orientation][move];
    //     edge_orientation = move_edge_orientation[edge_orientation][move];
    //     UDslice_edge_position = move_UDslice_edge_position[UDslice_edge_position][move];
    // }
    // cout << '\n';

    // CubieLevelCube cube;
    // input(&cube);
}
