#include <iostream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

int main()
{
    // CubieLevelCube cube;
    // input(&cube);

    generate_moving_tables();
    int x;
    Edges temp[8];
    cin >> x;
    UD_edge_permutation_to_cubie(x, temp);
    for (int i = 0; i < 8; i++)
        cout << temp[i] << " ";
    cout << '\n';

    cout << move_UD_edge_permutation[0][R2] << '\n';

    for (int move = 0; move < 18; move += 3)
    {
        if (move < 12)
        {
            cout << move  + 1 << ": ";
            UD_edge_permutation_to_cubie(move_UD_edge_permutation[x][move + 1], temp);
            for (int i = 0; i < 8; i++)
                cout << temp[i] << " ";
            cout << '\n';
        }
        else
            for (int j = 0; j < 3; j++)
            {
                cout << move + j << ": ";
                UD_edge_permutation_to_cubie(move_UD_edge_permutation[x][move + j], temp);
                for (int i = 0; i < 8; i++)
                    cout << temp[i] << " ";
                cout << '\n';
            }
    }
}