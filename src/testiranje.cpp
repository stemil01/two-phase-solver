#include <iostream>
#include <algorithm>
#include "coordinates.hpp"
#include "moves.hpp"
#include "search.hpp"
using namespace std;

void test_seach()
{
    int minS = 31, maxS = -1, sum = 0;
    for (int i = 0; i < 100; i++)
    {
        cout << i << ": ";
        Cube cube = random_moves(100);
        vector<int> solution;
        search(cube, 31, &solution);
        cout << "Resenje: ";
        for (int j = 0; j < solution.size(); j++)
            print_move(solution[j]);
        cout << "[ " << solution.size() << " ]" << '\n';

        minS = min(minS, (int)solution.size());
        maxS = max(maxS, (int)solution.size());
        sum += solution.size();
    }

    cout << "min \t" << minS << '\n';
    cout << "max \t" << maxS << '\n';
    cout << "avg \t" << (double)sum / 100 << '\n';
}

void test_improved_search(int time)
{
    int minS = 31, maxS = -1, sum = 0;
    for (int i = 0; i < 100; i++)
    {
        cout << i << ": ";
        Cube cube = random_moves(100);
        int len = improved_search(cube, time);

        minS = min(minS, len);
        maxS = max(maxS, len);
        sum += len;
    }

    cout << "min \t" << minS << '\n';
    cout << "max \t" << maxS << '\n';
    cout << "avg \t" << (double)sum / 100 << '\n';
}
