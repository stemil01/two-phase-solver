#include <iostream>
#include <queue>
#include "coordinates.hpp"
#include "moves.hpp"
using namespace std;

unsigned char phase1_pruning[NUM_PHASE1_PRUNING_TABLE]; 

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

void initialize_phase1_pruning()
{
    for (int i = 0; i < NUM_PHASE1_PRUNING_TABLE; i++)
        phase1_pruning[i] = ~0;
}

void generate_phase1_pruning_table()
{
    initialize_phase1_pruning();

    queue<unsigned int> q;    
    q.push(0);

    phase1_pruning[0] &= (~0 << 2); // postavljanje da je vrednost stanja 0, jednaka 0

    while (!q.empty())
    {
        int state = q.front();
        q.pop();

        int corner_orientation, edge_orientation, UDslice_edge_position;
        int index = state >> 4;
        int position = state & 4;
        int mask = 4 << 2 * position;
        int phase1_pruning_value = (phase1_pruning[index] & mask) >> (2 * position);

        int moved_corner_orientation, moved_edge_orientation, moved_UDslice_edge_position;
        int moved_state, moved_phase1_pruning_value;

        for (int move = 0; move < 18; move++)
        {
            moved_corner_orientation = move_corner_orientation[corner_orientation][move];
            moved_edge_orientation = move_edge_orientation[edge_orientation][move];
            moved_UDslice_edge_position = move_UDslice_edge_position[UDslice_edge_position][move];

            moved_state = get_phase1_state(moved_corner_orientation, moved_edge_orientation, moved_UDslice_edge_position);

            int moved_index = moved_state >> 4;
            int moved_position = moved_state & 4;
            int moved_mask = 4 << 2 * moved_position;

            if (phase1_pruning[index] & mask == mask) // ovo znaci da se nije pojavljivao do sad, tj. da ima vrednost 11
            {
                int moved_phase1_pruning_value = (phase1_pruning_value + 1) % 3;
                moved_phase1_pruning_value <<= 2 * moved_position;
                phase1_pruning[index] &= moved_phase1_pruning_value; // radice & zato sto je vec tamo vrednost 11 
                q.push(moved_state);
            }
        }
    }
}
