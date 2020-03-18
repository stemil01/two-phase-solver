#include <iostream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

// REDOSLED POTEZA
// R R2 R3 F F2 F3 L L2 L3 B B2 B3 U U2 U3 D D2 D3

void initialize_moves()
{
    move_corner[R][URF] = DFR;
    move_corner[R][UFL] = UFL;
    move_corner[R][ULB] = ULB;
    move_corner[R][UBR] = URF;
    move_corner[R][DFR] = DRB;
    move_corner[R][DLF] = DLF;
    move_corner[R][DBL] = DBL;
    move_corner[R][DRB] = UBR;


}