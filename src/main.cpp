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
    // generate_phase2_pruning_tables();

    // testiranje pretrage
    int corner_orientation = 0, edge_orientation = 0, UDslice_edge_position = 0;
    int corner_permutation = 0, UD_edge_permutation = 0, UDslice_edge_permutation = 0;

    cout << "Potezi za kocku: ";
    for (int i = 0; i < 20; i++)
    {
        int move = rand() % 18;
        string output;
        switch (move)
        {
        case 0:
            output = "R";
            break;
        case 1:
            output = "R2";
            break;
        case 2:
            output = "R3";
            break;
        case 3:
            output = "F";
            break;
        case 4:
            output = "F2";
            break;
        case 5:
            output = "F3";
            break;
        case 6:
            output = "L";
            break;
        case 7:
            output = "L2";
            break;
        case 8:
            output = "L3";
            break;
        case 9:
            output = "B";
            break;
        case 10:
            output = "B2";
            break;
        case 11:
            output = "B3";
            break;
        case 12:
            output = "U";
            break;
        case 13:
            output = "U2";
            break;
        case 14:
            output = "U3";
            break;
        case 15:
            output = "D";
            break;
        case 16:
            output = "D2";
            break;
        case 17:
            output = "D3";
            break;
        default:
            break;
        }
        cout << output << " ";

        corner_orientation = move_corner_orientation[corner_orientation][move];
        edge_orientation = move_edge_orientation[edge_orientation][move];
        UDslice_edge_position = move_UDslice_edge_position[UDslice_edge_position][move];

        corner_permutation = move_corner_permutation[corner_permutation][move];
        UD_edge_permutation = move_UD_edge_permutation[UD_edge_permutation][move];
        UDslice_edge_permutation = move_UDslice_edge_permutation[UDslice_edge_permutation][move];
    }
    cout << '\n';

    vector<int> v;
    test_phase1_search(corner_orientation, edge_orientation, UDslice_edge_position, &v);

    cout << "Resenje za prvu fazu bi trebalo da bude: ";
    for (int i = 0; i < v.size(); i++)
    {
        string output;
        switch (v[i])
        {
        case 0:
            output = "R";
            break;
        case 1:
            output = "R2";
            break;
        case 2:
            output = "R3";
            break;
        case 3:
            output = "F";
            break;
        case 4:
            output = "F2";
            break;
        case 5:
            output = "F3";
            break;
        case 6:
            output = "L";
            break;
        case 7:
            output = "L2";
            break;
        case 8:
            output = "L3";
            break;
        case 9:
            output = "B";
            break;
        case 10:
            output = "B2";
            break;
        case 11:
            output = "B3";
            break;
        case 12:
            output = "U";
            break;
        case 13:
            output = "U2";
            break;
        case 14:
            output = "U3";
            break;
        case 15:
            output = "D";
            break;
        case 16:
            output = "D2";
            break;
        case 17:
            output = "D3";
            break;
        default:
            break;
        }
        cout << output << " ";
        corner_permutation = move_corner_permutation[corner_permutation][v[i]];
        UD_edge_permutation = move_UD_edge_permutation[UD_edge_permutation][v[i]];
        UDslice_edge_permutation = move_UDslice_edge_permutation[UDslice_edge_permutation][v[i]];
    }
    cout << '\n';

    test_phase2_search(corner_permutation, UD_edge_permutation, UDslice_edge_permutation);

    // CubieLevelCube cube;
    // input(&cube);
}
