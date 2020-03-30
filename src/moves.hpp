#ifndef MOVES_HPP
#define MOVES_HPP

#include "definitions.hpp"

enum Moves : int {R, R2, R3, F, F2, F3, L, L2, L3, B, B2, B3, U, U2, U3, D, D2, D3};

// MOVING TABLES
extern int move_corner_orientation[NUM_CORNER_ORIENTATION][18];
extern int move_edge_orientation[NUM_EDGE_ORIENTATION][18];
extern int move_UDslice_edge_position[NUM_UDSLICE_EDGE_POSITION][18];

extern int move_corner_permutation[NUM_CORNER_PERMUTATION][18];             //////////////////////////////////////////////////////////////////////////////
extern int move_UDslice_edge_permutation[NUM_UDSLICE_EDGE_PERMUTATION][18]; // ovde ce biti po 10 poteza, ali zbog olaksica pravim matrice sa 18 kolona //
extern int move_UD_edge_permutation[NUM_UD_EDGE_PERMUTATION][18];           //////////////////////////////////////////////////////////////////////////////

// pomocni nizovi za pravljenje moving table-ova
extern int move_corner[18][8];
extern int move_edge[18][12];

extern int corner_orient[18][8][3];
extern int edge_orient[18][12][2];

void initialize_move_corner();
void initialize_move_edge();
void initialize_corner_orient();
void initialize_edge_orient();

// PHASE 1
void generate_move_corner_orientation();
void generate_move_edge_orientation();
void generate_move_UDslice_edge_position();

// PHASE 2
void generate_move_corner_permutation();
void generate_move_UD_edge_permutation();
void generate_move_UDslice_edge_permutation();

void initialize_moves();
void generate_moving_tables();

#endif // MOVES_HPP