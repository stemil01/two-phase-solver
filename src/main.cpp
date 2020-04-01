#include <iostream>
#include "coordinates.hpp"
#include "moves.hpp"
#include "pruning_tables.hpp"
using namespace std;

int main()
{
    // generate_moving_tables();

    // CubieLevelCube cube;
    // input(&cube);

    int a, b, c;
    unsigned int x;
    while (true)
    {
        cin >> x;
        get_phase1_coordinates(x, &a, &b, &c);
        cout << a << " " << b << " " << c << '\n';
        cout << get_phase1_state(a, b, c) << '\n';
    }
}
