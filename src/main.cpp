#include <iostream>
#include "coordinates.hpp"
#include "moves.hpp"
#include "pruning_tables.hpp"
using namespace std;

int main()
{
    generate_moving_tables();
    generate_phase1_pruning_table();

    // CubieLevelCube cube;
    // input(&cube);
}
