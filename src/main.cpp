#include <iostream>
#include "definitions.h"
using namespace std;

int main()
{
    CubieLevelCube cube;
    input(&cube);

    cout << "\n----------------" << '\n';
    for (int i = 0; i < 12; i++)
        cout << cube.edge_orientation[i] << " ";
    cout << '\n';

    int temp;
    cubie_to_edge_orientation(cube.edge_orientation, &temp);
    cout << temp << '\n';

    int temp_arr[12];
    edge_orientation_to_cubie(956, temp_arr);
    for (int i = 0; i < 12; i++)
        cout << temp_arr[i] << " ";
    cout << '\n';

    cubie_to_edge_orientation(temp_arr, &temp);
    cout << temp << '\n';
}