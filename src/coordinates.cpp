#include <iostream>
#include "definitions.h"
using namespace std;

void input(CubieLevelCube *cube)
{
    string tmp_replaced_by;
    int tmp_orientation;
    cout << "Corners: " << '\n';
    for (int i = 0; i < 8; i++)
    {
        cout << i << ": ";
        cin >> tmp_replaced_by >> tmp_orientation;

        if (tmp_replaced_by == "URF")
            cube->corner_permutation[i] = URF;
        else if (tmp_replaced_by == "UFL")
            cube->corner_permutation[i] = UFL;
        else if (tmp_replaced_by == "ULB")
            cube->corner_permutation[i] = ULB;
        else if (tmp_replaced_by == "UBR")
            cube->corner_permutation[i] = UBR;
        else if (tmp_replaced_by == "DFR")
            cube->corner_permutation[i] = DFR;
        else if (tmp_replaced_by == "DLF")
            cube->corner_permutation[i] = DLF;
        else if (tmp_replaced_by == "DBL")
            cube->corner_permutation[i] = DBL;
        else if (tmp_replaced_by == "DRB")
            cube->corner_permutation[i] = DRB;
        else
            cout << "Pogresan unos!" << '\n';

        cube->corner_orientation[i] = tmp_orientation;
    }
    cout << "Edges: " << '\n';
    for (int i = 0; i < 12; i++)
    {
        cout << i << ": ";
        cin >> tmp_replaced_by >> tmp_orientation;

        if (tmp_replaced_by == "UR")
            cube->edge_permutation[i] = UR;
        else if (tmp_replaced_by == "UF")
            cube->edge_permutation[i] = UF;
        else if (tmp_replaced_by == "UL")
            cube->edge_permutation[i]= UL;
        else if (tmp_replaced_by == "UB")
            cube->edge_permutation[i] = UB;
        else if (tmp_replaced_by == "DR")
            cube->edge_permutation[i] = DR;
        else if (tmp_replaced_by == "DF")
            cube->edge_permutation[i] = DF;
        else if (tmp_replaced_by == "DL")
            cube->edge_permutation[i] = DL;
        else if (tmp_replaced_by == "DB")
            cube->edge_permutation[i] = DB;
        else if (tmp_replaced_by == "FR")
            cube->edge_permutation[i] = FR;
        else if (tmp_replaced_by == "FL")
            cube->edge_permutation[i] = FL;
        else if (tmp_replaced_by == "BL")
            cube->edge_permutation[i] = BL;
        else if (tmp_replaced_by == "BR")
            cube->edge_permutation[i] = BR;
        else
            cout << "Pogresan unos!" << '\n';

        cube->edge_orientation[i] = tmp_orientation;
    }
}

void corner_orientation_to_cubie(int corner_orientation, int cubie_corner_orientation[])
{
    // ne gledam posledni cosak, jer njegovu orijentaciju mozemo da odredimo na osnovu ostalih
    int sum = 0;
    for (int i = 6; i >= 0; i--)
    {
        cubie_corner_orientation[i] = corner_orientation % 3;
        corner_orientation /= 3;
        sum += cubie_corner_orientation[i];
    }
    cubie_corner_orientation[7] = (3 - sum % 3) % 3;
}

void cubie_to_corner_orientation(int cubie_corner_orientation[], int *corner_orientation)
{
    // ne gledam posledni cosak, jer njegovu orijentaciju mozemo da odredimo na osnovu ostalih
    int deg = 1, res = 0;
    for (int i = 6; i >= 0; i--)
    {
        res += deg*cubie_corner_orientation[i];
        deg *= 3;
    }
    *corner_orientation = res;
}

void edge_orientation_to_cubie(int edge_orientation, int cubie_edge_orientation[])
{
    // ne gledamo poslednju ivicu jer njenu orijentaciju mozemo da odredimo iz orijentacija ostalih
    int sum = 0;
    for (int i = 10; i >= 0; i--)
    {
        cubie_edge_orientation[i] = edge_orientation % 2;
        edge_orientation /= 2;
        sum += cubie_edge_orientation[i];
    }
    cubie_edge_orientation[11] = (2 - sum % 2) % 2;
}

void cubie_to_edge_orientation(int cubie_edge_orientation[], int *edge_orientation)
{
    // ne gledamo poslednju ivicu jer njenu orijentaciju mozemo da odredimo iz orijentacija ostalih
    int deg = 1, res = 0;
    for (int i = 10; i >= 0; i--)
    {
        res += deg*cubie_edge_orientation[i];
        deg *= 2;
    }
    *edge_orientation = res;
}
