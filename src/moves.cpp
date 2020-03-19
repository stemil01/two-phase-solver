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

    move_corner[R][URF] = DFR;
    move_corner[R][UBR] = URF;
    move_corner[R][DRB] = UBR;
    move_corner[R][DFR] = DRB;

    move_corner[F][URF] = UFL;
    move_corner[F][DFR] = URF;
    move_corner[F][DLF] = DFR;
    move_corner[F][UFL] = DLF;

    move_corner[L][UFL] = ULB;
    move_corner[L][DLF] = UFL;
    move_corner[L][DBL] = DLF;
    move_corner[L][ULB] = DBL;

    move_corner[B][ULB] = UBR;
    move_corner[B][DBL] = ULB;
    move_corner[B][DRB] = DBL;
    move_corner[B][UBR] = DRB;

    move_corner[U][URF] = UBR;
    move_corner[U][UFL] = URF;
    move_corner[U][ULB] = UFL;
    move_corner[U][UBR] = ULB;

    move_corner[D][DFR] = DLF;
    move_corner[D][DRB] = DFR;
    move_corner[D][DBL] = DRB;
    move_corner[D][DLF] = DBL;
}

void initialize_move_edge()
{
    for (int move = 0; move < 18; move++)
        for (int edge = 0; edge < 12; edge++)
            move_edge[move][edge] = edge;
        
    move_edge[R][UR] = FR;
    move_edge[R][BR] = UR;
    move_edge[R][DR] = BR;
    move_edge[R][FR] = DR;

    move_edge[F][UF] = FL;
    move_edge[F][FR] = UF;
    move_edge[F][DF] = FR;
    move_edge[F][FL] = DF;

    move_edge[L][UL] = BL;
    move_edge[L][FL] = UL;
    move_edge[L][DL] = FL;
    move_edge[L][BL] = DL;
    
    move_edge[B][UB] = BR;
    move_edge[B][BL] = UB;
    move_edge[B][DB] = BL;
    move_edge[B][BR] = DB;

    move_edge[U][UR] = UB;
    move_edge[U][UF] = UR;
    move_edge[U][UL] = UF;
    move_edge[U][UB] = UL;

    move_edge[D][DR] = DF;
    move_edge[D][DB] = DR;
    move_edge[D][DL] = DB;
    move_edge[D][DF] = DL;
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

void generate_moving_tables()
{
    initialize_moves();
    generate_move_corner_orientation();
    generate_move_edge_orientation();
    generate_move_UDslice_edge_position();
    generate_move_corner_permutation();
    generate_move_UD_edge_permutation();
    generate_move_UDslice_edge_permutation();
}
