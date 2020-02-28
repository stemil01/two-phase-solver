#include <iostream>
#include "definitions.h"
using namespace std;

void input(CubieLevelCube *cube)
{
    string tmp_replaced_by;
    char tmp_orientation;
    cout << "Corners: " << '\n';
    for (int i = 0; i < 8; i++)
    {
        cout << i << ": ";
        cin >> tmp_replaced_by >> tmp_orientation;

        if (tmp_replaced_by == "URF")
            cube->corner[i].replaced_by = URF;
        else if (tmp_replaced_by == "UFL")
            cube->corner[i].replaced_by = UFL;
        else if (tmp_replaced_by == "ULB")
            cube->corner[i].replaced_by = ULB;
        else if (tmp_replaced_by == "UBR")
            cube->corner[i].replaced_by = UBR;
        else if (tmp_replaced_by == "DFR")
            cube->corner[i].replaced_by = DFR;
        else if (tmp_replaced_by == "DLF")
            cube->corner[i].replaced_by = DLF;
        else if (tmp_replaced_by == "DBL")
            cube->corner[i].replaced_by = DBL;
        else if (tmp_replaced_by == "DRB")
            cube->corner[i].replaced_by = DRB;
        else
            cout << "Pogresan unos!" << '\n';

        cube->corner[i].orientation = tmp_orientation;
    }
    cout << "Edges: " << '\n';
    for (int i = 0; i < 12; i++)
    {
        cout << i << ": ";
        cin >> tmp_replaced_by >> tmp_orientation;

        if (tmp_replaced_by == "UR")
            cube->edge[i].replaced_by = UR;
        else if (tmp_replaced_by == "UF")
            cube->edge[i].replaced_by = UF;
        else if (tmp_replaced_by == "UL")
            cube->edge[i].replaced_by = UL;
        else if (tmp_replaced_by == "UB")
            cube->edge[i].replaced_by = UB;
        else if (tmp_replaced_by == "DR")
            cube->edge[i].replaced_by = DR;
        else if (tmp_replaced_by == "DF")
            cube->edge[i].replaced_by = DF;
        else if (tmp_replaced_by == "DL")
            cube->edge[i].replaced_by = DL;
        else if (tmp_replaced_by == "DB")
            cube->edge[i].replaced_by = DB;
        else if (tmp_replaced_by == "FR")
            cube->edge[i].replaced_by = FR;
        else if (tmp_replaced_by == "FL")
            cube->edge[i].replaced_by = FL;
        else if (tmp_replaced_by == "BL")
            cube->edge[i].replaced_by = BL;
        else if (tmp_replaced_by == "BR")
            cube->edge[i].replaced_by = BR;
        else
            cout << "Pogresan unos!" << '\n';

        cube->edge[i].orientation = tmp_orientation;
    }
}

int to_corner_orientation(Corner corner[])
{
    
}
