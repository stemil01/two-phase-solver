#include <iostream>
#include <queue>
#include "coordinates.hpp"
#include "moves.hpp"
using namespace std;

unsigned char phase1_pruning[554273280]; // ukupan broj razlicitih kombinacija u prvoj fazi je 2217093120 
                                // ovo je 1/4 zato sto u svakoj cuvamo po 4 vrednosti (svaka ima po 2 bita)

unsigned int get_phase1_state(int corner_orientation, int edge_orientation, int UDslice_edge_position)
{
    unsigned int A = NUM_EDGE_ORIENTATION * NUM_UDSLICE_EDGE_POSITION;
    unsigned int B = NUM_UDSLICE_EDGE_POSITION;
    return (unsigned int)corner_orientation * A + (unsigned int)edge_orientation * B + (unsigned int)UDslice_edge_position;
}

void get_phase1_coordinates(unsigned int state, int* corner_orientation, int* edge_orientation, int* UDslice_edge_position)
{
    unsigned int A = NUM_EDGE_ORIENTATION * NUM_UDSLICE_EDGE_POSITION;
    unsigned int B = NUM_UDSLICE_EDGE_POSITION;

    *UDslice_edge_position = state % NUM_UDSLICE_EDGE_POSITION;
    state /= NUM_UDSLICE_EDGE_POSITION;
    *edge_orientation = state % NUM_EDGE_ORIENTATION;
    state /= NUM_EDGE_ORIENTATION;
    *corner_orientation = state;
}

void generate_phase1_pruning_table()
{
    queue<unsigned int> q;    
    q.push(0);

    while (!q.empty())
    {
        int state = q.front();
        q.pop();

        int corner_orientation, edge_orientation, UDslice_edge_position;
        int moved_corner_orientation, moved_edge_orientation, moved_UDslice_edge_position;
        int moved_state;

        for (int move = 0; move < 18; move++)
        {
            moved_corner_orientation = move_corner_orientation[corner_orientation][move];
            moved_edge_orientation = move_edge_orientation[edge_orientation][move];
            moved_UDslice_edge_position = move_UDslice_edge_position[UDslice_edge_position][move];

            moved_state = get_phase1_state(moved_corner_orientation, moved_edge_orientation, moved_UDslice_edge_position);
        }
    }
}
