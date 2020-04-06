#include <iostream>
#include "moves.hpp"
#include "pruning_tables.hpp"
using namespace std;

void test_phase1_search(int corner_orientation, int edge_orientation, int UDslice_edge_position)
{
    cout << "Resenje za prvu fazu bi trebalo da bude: ";

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

                cout << move << " ";
            }
        }
    }
    cout << '\n';
}
