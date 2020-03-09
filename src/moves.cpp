#include <iostream>
#include "definitions.h"
#include "moves.h"
using namespace std;

// REDOSLED POTEZA
// R R2 R3 F F2 F3 L L2 L3 B B2 B3 U U2 U3 D D2 D3

void initialize_move_corner_orientation()
{
    move_corner_orienation[R][URF][0] = 1;
}