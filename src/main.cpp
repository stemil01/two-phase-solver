#include <iostream>
#include <string.h>
#include "definitions.h"
using namespace std;

int main()
{
    CubieLevelCube cube;
    input(&cube);

    cout << "Pisem kocku..." << '\n';

    for (int i = 0; i < 20; i++)
        cout << i << ": " << int(cube.cubie[i].replaced_by) << " " << char(cube.cubie[i].orientation) << '\n';
}