#include <iostream>
#include "definitions.h"
using namespace std;

int main()
{
    // CubieLevelCube cube;
    // input(&cube);

    int temp_num;
    bool temp_arr[12] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    
    for (int i = 0; i < 12; i++)
        cout << temp_arr[i] << " ";
    cout << '\n';

    while (true)
    {
        cin >> temp_num;
        UDslice_edge_position_to_cubie(temp_num, temp_arr);
        for (int i = 0; i < 12; i++)
            cout << temp_arr[i] << " ";
        cout << '\n';

        cubie_to_UDslice_edge_position(temp_arr, &temp_num);
        cout << temp_num << '\n';
    }
}