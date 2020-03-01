#include <iostream>
#include "definitions.h"
using namespace std;

int main()
{
    cout << Corners(0) << '\n';
    // CubieLevelCube cube;
    // input(&cube);

    int temp_num;
    // Corners temp_arr[8] = {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};
    // Corners temp_arr[8] = {DRB, DBL, DLF, DFR, UBR, ULB, UFL, URF};
    Corners temp_arr[8] = {DBL, DRB, DLF, DFR, UBR, ULB, UFL, URF};
    
    for (int i = 0; i < 8; i++)
        cout << temp_arr[i] << " ";
    cout << '\n';

    /*
    while (true)
    {
        cin >> temp_num;
        corner_permutation_to_cubie(temp_num, temp_arr);
        for (int i = 0; i < 8; i++)
            cout << temp_arr[i] << " ";
        cout << '\n';

        cubie_to_corner_permutation(temp_arr, &temp_num);
        cout << temp_num << '\n';
    }
    */

    cubie_to_corner_permutation(temp_arr, &temp_num);
    cout << temp_num << '\n';
}