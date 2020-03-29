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
    for (int move = 0; move < 18; move++)
        for (int corner = 0; corner < 8; corner++)
            for (int orient = 0; orient < 3; orient++)
                corner_orient[move][corner][orient] = orient;

    cout << "e brt usao sam ovde" << '\n';

    // R
    corner_orient[R][URF][0] = 2;
    corner_orient[R][URF][1] = 0;
    corner_orient[R][URF][2] = 1;

    corner_orient[R][UBR][0] = 1;
    corner_orient[R][UBR][1] = 2;
    corner_orient[R][UBR][2] = 0;

    corner_orient[R][DRB][0] = 2;
    corner_orient[R][DRB][1] = 0;
    corner_orient[R][DRB][2] = 1;

    corner_orient[R][DFR][0] = 1;
    corner_orient[R][DFR][1] = 2;
    corner_orient[R][DFR][2] = 0;

    // F
    corner_orient[F][URF][0] = 1;
    corner_orient[F][URF][1] = 2;
    corner_orient[F][URF][2] = 0;

    corner_orient[F][DFR][0] = 2;
    corner_orient[F][DFR][1] = 0;
    corner_orient[F][DFR][2] = 1;

    corner_orient[F][DLF][0] = 1;
    corner_orient[F][DLF][1] = 2;
    corner_orient[F][DLF][2] = 0;

    corner_orient[F][UFL][0] = 2;
    corner_orient[F][UFL][1] = 0;
    corner_orient[F][UFL][2] = 1;
    
    // L
    corner_orient[L][UFL][0] = 1;
    corner_orient[L][UFL][1] = 2;
    corner_orient[L][UFL][2] = 0;

    corner_orient[L][DLF][0] = 2;
    corner_orient[L][DLF][1] = 0;
    corner_orient[L][DLF][2] = 1;

    corner_orient[L][DBL][0] = 1;
    corner_orient[L][DBL][1] = 2;
    corner_orient[L][DBL][2] = 0;

    corner_orient[L][ULB][0] = 2;
    corner_orient[L][ULB][1] = 0;
    corner_orient[L][ULB][2] = 1;

    // B
    corner_orient[B][ULB][0] = 1;
    corner_orient[B][ULB][1] = 2;
    corner_orient[B][ULB][2] = 0;

    corner_orient[B][DBL][0] = 2;
    corner_orient[B][DBL][1] = 0;
    corner_orient[B][DBL][2] = 1;

    corner_orient[B][DRB][0] = 1;
    corner_orient[B][DRB][1] = 2;
    corner_orient[B][DRB][2] = 0;

    corner_orient[B][UBR][0] = 2;
    corner_orient[B][UBR][1] = 0;
    corner_orient[B][UBR][2] = 1;
}

void initialize_edge_orient()
{
    for (int move = 0; move < 18; move++)
        for (int edge = 0; edge < 8; edge++)
            for (int orient = 0; orient < 2; orient++)
                corner_orient[move][edge][orient] = orient;
    
    // F
    edge_orient[F][UF][0] = 1;
    edge_orient[F][UF][1] = 0;

    edge_orient[F][FR][0] = 1;
    edge_orient[F][FR][1] = 0;

    edge_orient[F][DF][0] = 1;
    edge_orient[F][DF][1] = 0;

    edge_orient[F][FL][0] = 1;
    edge_orient[F][FL][1] = 0;

    // B
    edge_orient[B][UB][0] = 1;
    edge_orient[B][UB][1] = 0;

    edge_orient[B][BL][0] = 1;
    edge_orient[B][BL][1] = 0;

    edge_orient[B][DB][0] = 1;
    edge_orient[B][DB][1] = 0;

    edge_orient[B][BR][0] = 1;
    edge_orient[B][BR][1] = 0;
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
