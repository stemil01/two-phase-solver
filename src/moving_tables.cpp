#include <iostream>
#include "definitions.h"
#include "moves.h"
using namespace std;

// PHASE 1
void moving_generate_corner_orientation()
{
    for (int i = 0; i < NUM_CORNER_ORIENTATION; i++)
    {
        int cubie_corner_orientation[8];
        corner_orientation_to_cubie(i, cubie_corner_orientation);

        for (int move = 0; move < 18; move += 3)
        {
            int moved[8];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    int res;
                    moved[j + i] = move_corner_orienation[move][j][cubie_corner_orientation[j]];
                    cubie_to_corner_orientation(moved, &res);
                    cout << res << " ";
                }
            }
        }
        cout << '\n';
    }
}