#include <iostream>
#include <vector>
#include "coordinates.hpp"
#include "moves.hpp"
#include "pruning_tables.hpp"
#include "search.hpp"
using namespace std;

int main()
{
    generate_moving_tables();
    generate_phase1_pruning_table();
    generate_phase2_pruning_tables();

    bool go_on = true;
    while (go_on)
    {
        Cube cube = random_moves(30);
        improve_search(cube, 5000);

        cin >> go_on;
    }
}
