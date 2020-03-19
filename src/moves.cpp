#include <iostream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

// REDOSLED POTEZA
// R R2 R3 F F2 F3 L L2 L3 B B2 B3 U U2 U3 D D2 D3

void initialize_move_corner()
{
    for (int move = 0; move < 18; move++)
        for (int corner = 0; corner < 8; corner++)
            move_corner[move][corner] = corner;

        
}

void initialize_edge_corner()
{
    for (int move = 0; move < 18; move++)
        for (int edge = 0; edge < 12; edge++)
            move_edge[move][edge] = edge;
}

void initialize_corner_orient()
{
    for (int corner = 0; corner < 8; corner++)
        for (int orient = 0; orient < 3; orient++)
            corner_orient[corner][corner][orient] = orient;
}

void initialize_edge_orient()
{
    for (int edge = 0; edge < 8; edge++)
        for (int orient = 0; orient < 2; orient++)
            corner_orient[edge][edge][orient] = orient;
}

void initialize_moves()
{
    initialize_move_corner();
    initialize_move_edge();
    initialize_corner_orient();
    initialize_edge_orient();
}

void generate_moveing_tables()
{
    initialize_moves();
    generate_move_corner_orientation();
    generate_move_edge_orientation();
    generate_move_UDslice_edge_postition();
    generate_move_corner_permutation();
    generate_move_UD_edge_permutation();
    generate_move_UDslice_edge_permutation();
}
