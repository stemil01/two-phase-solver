#include <iostream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

int main()
{
    // CubieLevelCube cube;
    // input(&cube);

    // generate_moveing_tables();
    initialize_move_corner();
    generate_move_corner_permutation();

    Corners temp[8];
    corner_permutation_to_cubie(15, temp);
    for (int i = 0; i < 8; i++)
        cout << temp[i] << " ";
    cout << '\n';
    
    corner_permutation_to_cubie(move_corner_permutation[15][U], temp);
    for (int i = 0; i < 8; i++)
        cout << temp[i] << " ";
    cout << '\n';
}