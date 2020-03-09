#ifndef MOVES_H
#define MOVES_H

enum Moves : int {R, F, L, B, U, D};

int move_corner_orienation[6][8][3];

void initialize_move_corner_orientation();

// PHASE 1
void moving_generate_corner_orientation();

#endif // MOVES_H