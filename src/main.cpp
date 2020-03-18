#include <iostream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

int main()
{
    // CubieLevelCube cube;
    // input(&cube);

    bool nesto[12];
    UDslice_edge_position_to_cubie(0, nesto);
    for (int i = 0; i < 12; i++)
        cout << nesto[i] << " ";
    cout << '\n';
}