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
    cubie_corner_orientation[7] = 3 - sum % 3;
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
    cubie_edge_orientation[11] = 2 - sum % 2;
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

void UDslice_edge_position_to_cubie(int UDslice_edge_position, bool cubie_UDslice_edge_position[])
{
    int p[5], i = 1;
    p[0] = 12;
    for (int i = 1; i < 5; i++)
    {
        int ind = p[i - 1] - 1, value;
        switch (i)
        {
        case 1:
            value = ind*(ind - 1)*(ind - 2)/6;
            break;
        case 2:
            value = ind*(ind - 1)/2;
            break;
        case 3:
            value = ind;
            break;
        case 4:
            value = 1;
        default:
            break;
        }
        while (UDslice_edge_position >= value)   
        {
            UDslice_edge_position -= value;
            ind--;

            switch (i)
            {
            case 1:
                value = ind*(ind - 1)*(ind - 2)/6;
                break;
            case 2:
                value = ind*(ind - 1)/2;
                break;
            case 3:
                value = ind;
                break;
            case 4:
                value = 1;
            default:
                break;
            }
        }
        p[i] = ind;
    }

    for (int i = 0; i < 12; i++)
    {
        if (i == p[1] || i == p[2] || i == p[3] || i == p[4])
            cubie_UDslice_edge_position[i] = true;
        else
            cubie_UDslice_edge_position[i] = false;
    }
}

void cubie_to_UDslice_edge_position(bool cubie_UDslice_edge_postition[], int *UDslice_edge_position)
{
    int p[5], ind = 1, res = 0;
    p[0] = 12;
    for (int i = 11; i >= 0; i--)
        if (cubie_UDslice_edge_postition[i] == true)
            p[ind++] = i;
    
    for (int i = 1; i < 5; i++)
        for (int j = p[i] + 1; j <= p[i - 1] - 1; j++)
        {
            int value;
            switch (i)
            {
            case 1:
                value = j*(j - 1)*(j - 2)/6;
                break;
            case 2:
                value = j*(j - 1)/2;
                break;
            case 3:
                value = j;
                break;
            case 4:
                value = 1;
            default:
                break;
            }
            res += value;
        }    
    *UDslice_edge_position = res;
}
