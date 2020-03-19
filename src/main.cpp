#include <iostream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

int main()
{
    // CubieLevelCube cube;
    // input(&cube);

    // generate_moveing_tables();
    initialize_move_edge();
    generate_move_UD_edge_permutation();

    Edges temp[8];
    UD_edge_permutation_to_cubie(0, temp);
    for (int i = 0; i < 8; i++)
        cout << temp[i] << " ";
    cout << '\n';
    
    UD_edge_permutation_to_cubie(move_UD_edge_permutation[0][U], temp);
    for (int i = 0; i < 8; i++)
        cout << temp[i] << " ";
    cout << '\n';
}