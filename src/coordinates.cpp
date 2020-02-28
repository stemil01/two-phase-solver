#include <iostream>
#include "definitions.h"
using namespace std;

void input(CubieLevelCube *cube)
{
    string tmp_replaced_by;
    char tmp_orientation;
    int i = 0;
    cout << "Corners: " << '\n';
    while (i < 8)
    {
        cout << i << ": ";
        cin >> tmp_replaced_by >> tmp_orientation;

        if (tmp_replaced_by == "URF")
            cube->cubie[i].replaced_by = URF;
        else if (tmp_replaced_by == "UFL")
            cube->cubie[i].replaced_by = UFL;
        else if (tmp_replaced_by == "ULB")
            cube->cubie[i].replaced_by = ULB;
        else if (tmp_replaced_by == "UBR")
            cube->cubie[i].replaced_by = UBR;
        else if (tmp_replaced_by == "DFR")
            cube->cubie[i].replaced_by = DFR;
        else if (tmp_replaced_by == "DLF")
            cube->cubie[i].replaced_by = DLF;
        else if (tmp_replaced_by == "DBL")
            cube->cubie[i].replaced_by = DBL;
        else if (tmp_replaced_by == "DRB")
            cube->cubie[i].replaced_by = DRB;
        else
            cout << "Pogresan unos!" << '\n';

        cube->cubie[i].orientation = tmp_orientation;
        i++;
    }
    cout << "Edges: " << '\n';
    while (i < 20)
    {
        cout << i - 8 << ": ";
        cin >> tmp_replaced_by >> tmp_orientation;

        if (tmp_replaced_by == "UR")
            cube->cubie[i].replaced_by = UR;
        else if (tmp_replaced_by == "UF")
            cube->cubie[i].replaced_by = UF;
        else if (tmp_replaced_by == "UL")
            cube->cubie[i].replaced_by = UL;
        else if (tmp_replaced_by == "UB")
            cube->cubie[i].replaced_by = UB;
        else if (tmp_replaced_by == "DR")
            cube->cubie[i].replaced_by = DR;
        else if (tmp_replaced_by == "DF")
            cube->cubie[i].replaced_by = DF;
        else if (tmp_replaced_by == "DL")
            cube->cubie[i].replaced_by = DL;
        else if (tmp_replaced_by == "DB")
            cube->cubie[i].replaced_by = DB;
        else if (tmp_replaced_by == "FR")
            cube->cubie[i].replaced_by = FR;
        else if (tmp_replaced_by == "FL")
            cube->cubie[i].replaced_by = FL;
        else if (tmp_replaced_by == "BL")
            cube->cubie[i].replaced_by = BL;
        else if (tmp_replaced_by == "BR")
            cube->cubie[i].replaced_by = BR;
        else
            cout << "Pogresan unos!" << '\n';

        cube->cubie[i].orientation = tmp_orientation;
        i++;
    }
}
