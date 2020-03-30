#include <iostream>
#include <fstream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

int main()
{
    // CubieLevelCube cube;
    // input(&cube);

    generate_moving_tables();
    int x;
    Edges temp[4];
    cin >> x;
    UDslice_edge_permutation_to_cubie(x, temp);
    for (int i = 0; i < 4; i++)
        cout << temp[i] << " ";
    cout << '\n';

    for (int move = 0; move < 18; move += 3)
    {
        if (move < 12)
        {
            cout << move  + 1 << ": ";
            UDslice_edge_permutation_to_cubie(move_UDslice_edge_permutation[x][move + 1], temp);
            for (int i = 0; i < 4; i++)
                cout << temp[i] << " ";
            cout << '\n';
        }
        else
            for (int j = 0; j < 3; j++)
            {
                cout << move + j << ": ";
                UDslice_edge_permutation_to_cubie(move_UDslice_edge_permutation[x][move + j], temp);
                for (int i = 0; i < 4; i++)
                    cout << temp[i] << " ";
                cout << '\n';
            }
    }
}