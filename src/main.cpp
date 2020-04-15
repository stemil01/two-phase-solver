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

    // testiranje pretrage
    while (true)
    {
        Cube cube = random_moves();
        vector<int> solution;
        search(cube, &solution);

        for (int i = 0; i < solution.size(); i++)
            print_move(solution[i]);
        cout << "[ " << solution.size() << " ]" << '\n';
    }
}
