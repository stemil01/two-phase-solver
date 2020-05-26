#include <iostream>
#include <vector>
#include "coordinates.hpp"
#include "moves.hpp"
#include "pruning_tables.hpp"
#include "search.hpp"
#include "testiranje.hpp"
using namespace std;

int main()
{
    generate_moving_tables();
    generate_phase1_pruning_table();
    generate_phase2_pruning_tables();

    // testiranje 
    // test_seach();
    // test_improved_search(500);

    bool go_on = true;
    while (go_on)
    {  
        // input(); // za rucni unos
        Cube cube = random_moves(30); // za generisanje proizvoljne pozicije
        improved_search(cube, 2000);

        cin >> go_on;
    }
}
