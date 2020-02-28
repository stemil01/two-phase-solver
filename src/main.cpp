#include <iostream>
#include "definitions.h"
using namespace std;

int main()
{
    CubieLevelCube cube;
    input(&cube);

    cout << "Pisem kocku..." << '\n';

    for (int i = 0; i < 8; i++)
        cout << i << ": " << int(cube.corner[i].replaced_by) << " " << char(cube.corner[i].orientation) << '\n';
    for (int i = 0; i < 12; i++)
        cout << i << ": " << int(cube.edge[i].replaced_by) << " " << char(cube.edge[i].orientation) << '\n';
}