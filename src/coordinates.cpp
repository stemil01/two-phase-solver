#include <iostream>
#include "coordinates.hpp"
#include "moves.hpp"
using namespace std;

Cube input()
{
    string tmp_replaced_by;
    Corners cubie_corner_permutation[8];
    int cubie_corner_orientation[8];
    Edges cubie_edge_permutation[12];
    int cubie_edge_orientation[12];

    int tmp_orientation;
    cout << "Corners: " << '\n';
    for (int i = 0; i < 8; i++)
    {
        cout << i << ": ";
        cin >> tmp_replaced_by >> tmp_orientation;

        if (tmp_replaced_by == "URF")
            cubie_corner_permutation[i] = URF;
        else if (tmp_replaced_by == "UFL")
            cubie_corner_permutation[i] = UFL;
        else if (tmp_replaced_by == "ULB")
            cubie_corner_permutation[i] = ULB;
        else if (tmp_replaced_by == "UBR")
            cubie_corner_permutation[i] = UBR;
        else if (tmp_replaced_by == "DFR")
            cubie_corner_permutation[i] = DFR;
        else if (tmp_replaced_by == "DLF")
            cubie_corner_permutation[i] = DLF;
        else if (tmp_replaced_by == "DBL")
            cubie_corner_permutation[i] = DBL;
        else if (tmp_replaced_by == "DRB")
            cubie_corner_permutation[i] = DRB;
        else
            cout << "Pogresan unos!" << '\n';

        cubie_corner_orientation[i] = tmp_orientation;
    }
    cout << "Edges: " << '\n';
    for (int i = 0; i < 12; i++)
    {
        cout << i << ": ";
        cin >> tmp_replaced_by >> tmp_orientation;

        if (tmp_replaced_by == "UR")
            cubie_edge_permutation[i] = UR;
        else if (tmp_replaced_by == "UF")
            cubie_edge_permutation[i] = UF;
        else if (tmp_replaced_by == "UL")
            cubie_edge_permutation[i]= UL;
        else if (tmp_replaced_by == "UB")
            cubie_edge_permutation[i] = UB;
        else if (tmp_replaced_by == "DR")
            cubie_edge_permutation[i] = DR;
        else if (tmp_replaced_by == "DF")
            cubie_edge_permutation[i] = DF;
        else if (tmp_replaced_by == "DL")
            cubie_edge_permutation[i] = DL;
        else if (tmp_replaced_by == "DB")
            cubie_edge_permutation[i] = DB;
        else if (tmp_replaced_by == "FR")
            cubie_edge_permutation[i] = FR;
        else if (tmp_replaced_by == "FL")
            cubie_edge_permutation[i] = FL;
        else if (tmp_replaced_by == "BL")
            cubie_edge_permutation[i] = BL;
        else if (tmp_replaced_by == "BR")
            cubie_edge_permutation[i] = BR;
        else
            cout << "Pogresan unos!" << '\n';

        cubie_edge_orientation[i] = tmp_orientation;
    }
    Cube cube;
    cubie_to_corner_orientation(cubie_corner_orientation, &cube.corner_orientation);
    cubie_to_edge_orientation(cubie_edge_orientation, &cube.edge_orientation);

    bool cubie_UDslice_edge_position[12];
    for (int i = 0; i < 12; i++)
    {
        if (cubie_edge_permutation[i] == FR || cubie_edge_permutation[i] == FL || cubie_edge_permutation[i] == BL || cubie_edge_permutation[i] == BR)
            cubie_UDslice_edge_position[i] = true;
        else
            cubie_UDslice_edge_position[i] = false;
    }
    cubie_to_UDslice_edge_position(cubie_UDslice_edge_position, &cube.UDslice_edge_position);
    for (int i = 0; i < 12; i++)
        cube.cubie_edge_permutation[i] = cubie_edge_permutation[i];

    return cube;
}

Cube move_cube(Cube cube, int move)
{
    Cube moved_cube;

    moved_cube.corner_orientation = move_corner_orientation[cube.corner_orientation][move];
    moved_cube.edge_orientation = move_edge_orientation[cube.edge_orientation][move];
    moved_cube.UDslice_edge_position = move_UDslice_edge_position[cube.UDslice_edge_position][move];

    moved_cube.corner_permutation = move_corner_permutation[cube.corner_permutation][move];

    Edges moved[12];
    int base_move = (move / 3) * 3;
    int rem_move = move % 3;
    for (int j = 0; j <= rem_move; j++)
    {
        for (int k = 0; k < 12; k++)
            moved[k] = cube.cubie_edge_permutation[move_edge[base_move][k]];
        for (int k = 0; k < 12; k++)
            cube.cubie_edge_permutation[k] = moved[k];
    }

    for (int i = 0; i < 12; i++)
        moved_cube.cubie_edge_permutation[i] = cube.cubie_edge_permutation[i];

    return moved_cube;
}

Cube random_moves(int num_moves)
{
    srand(time(NULL));

    Cube cube;
    cube.corner_orientation = 0;
    cube.edge_orientation = 0;
    cube.UDslice_edge_position = 0;
    cube.corner_permutation = 0;

    for (int i = 0; i < 12; i++)
        cube.cubie_edge_permutation[i] = (Edges)i;

    cout << "Potezi za kocku: ";
    for (int i = 0; i < num_moves; i++)
    {
        int move = rand() % 18;
        print_move(move);
        cube = move_cube(cube, move);
    }
    cout << '\n';

    return cube;
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

// ovo je moglo jednostavnije da se napise
// https://en.wikipedia.org/wiki/Combinatorial_number_system
void UDslice_edge_position_to_cubie(int UDslice_edge_position, bool cubie_UDslice_edge_position[])
{
    // gledamo sa desna radi jednostavnosti
    int p[5];
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
    // gledamo sa desna radi jednostavnosti
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

void corner_permutation_to_cubie(int corner_permutation, Corners cubie_corner_permutation[])
{
    // gledamo sa desna na levo, radi jednostavnijeg "koda"
    int digit[8], base[8];
    digit[0] = 0;
    base[0] = 1;
    cubie_corner_permutation[0] = Corners(0);
    for (int i = 1; i < 8; i++)
    {
        base[i] = i*base[i - 1];
        cubie_corner_permutation[i] = Corners(0); 
    }

    for (int i = 7; i >= 1; i--)
    {
        digit[i] = corner_permutation / base[i];
        corner_permutation %= base[i];
    }

    for (int i = 7; i >= 1; i--)
    {
        int count = 0, j = 8;
        while (count <= digit[i])
        {
            j--;
            if (cubie_corner_permutation[j] < i)
                count++;
        }
        cubie_corner_permutation[j] = Corners(i);
    }
}

void cubie_to_corner_permutation(Corners cubie_corner_permutation[], int *corner_permutation)
{
    // gledamo sa desna na levo, radi jednostavnijeg "koda"
    int digit[8], base[8], res = 0;
    base[0] = 1;
    for (int i = 1; i < 8; i++)
    {
        digit[i] = 0;
        base[i] = i*base[i - 1];
    }

    for (int i = 1; i < 8; i++)
    {
        int j = 7;
        while (cubie_corner_permutation[j] != i)
        {
            if (cubie_corner_permutation[j] < i)
                digit[i]++;
            j--;
        }
    }

    for (int i = 1; i < 8; i++)
        res += digit[i]*base[i];

    *corner_permutation = res;
}

void UDslice_edge_permutation_to_cubie(int UDslice_edge_permutation, Edges cubie_UDslice_edge_permutation[])
{
    // gledamo sa desna na levo, radi jednostavnijeg "koda"
    // ivice UD isecka su FR, FL, BL i BR, dakle, uzimaju vrednosti iz skupa {8, 9, 10, 11},
    // zato uvodimo male razlike u odnosu na corner_permutation
    int digit[12], base[4];
    digit[8] = 0;
    base[0] = 1;
    cubie_UDslice_edge_permutation[0] = Edges(8);
    for (int i = 1; i < 4; i++)
    {
        base[i] = i*base[i - 1];
        cubie_UDslice_edge_permutation[i] = Edges(8);
    }

    for (int i = 11; i >= 9; i--)
    {
        digit[i] = UDslice_edge_permutation / base[i - 8];
        UDslice_edge_permutation %= base[i - 8];
    }

    for (int i = 11; i >= 9; i--)
    {
        int count = 0, j = 4;
        while (count <= digit[i])
        {
            j--;
            if (cubie_UDslice_edge_permutation[j] < i)
                count++;
        }
        cubie_UDslice_edge_permutation[j] = Edges(i);
    }
}

void cubie_to_UDslice_edge_permutation(Edges cubie_UDslice_edge_permutation[], int *UDslice_edge_permutation)
{
    // gledamo sa desna na levo, radi jednostavnijeg "koda"
    // ivice UD isecka su FR, FL, BL i BR, dakle, uzimaju vrednosti iz skupa {8, 9, 10, 11},
    // zato uvodimo male razlike u odnosu na corner_permutation
    int digit[12], base[4], res = 0;
    base[0] = 1;
    for (int i = 1; i < 4; i++)
    {
        digit[i + 8] = 0;
        base[i] = i*base[i - 1];
    }

    for (int i = 9; i < 12; i++)
    {
        int j = 3;
        while (cubie_UDslice_edge_permutation[j] != i)
        {
            if (cubie_UDslice_edge_permutation[j] < i)
                digit[i]++;
            j--;
        }
    }

    for (int i = 9; i < 12; i++)
        res += digit[i]*base[i - 8];

    *UDslice_edge_permutation = res;
}

void UD_edge_permutation_to_cubie(int UD_edge_permutation, Edges cubie_UD_edge_permutation[])
{
    // gledamo sa desna na levo, radi jednostavnijeg "koda"
    // UD ivice su UR, UF, UL, UB, DR, DF, DL, DB dakle, uzimaju vrednosti iz skupa {0, 1, 2, 3, 4, 5, 6, 7},
    // zato je gotovo identicno kao corner_permutation
    int digit[8], base[8];
    digit[0] = 0;
    base[0] = 1;
    cubie_UD_edge_permutation[0] = Edges(0);
    for (int i = 1; i < 8; i++)
    {
        base[i] = i*base[i - 1];
        cubie_UD_edge_permutation[i] = Edges(0);
    }

    for (int i = 7; i >= 1; i--)
    {
        digit[i] = UD_edge_permutation / base[i];
        UD_edge_permutation %= base[i];
    }

    for (int i = 7; i >= 1; i--)
    {
        int count = 0, j = 8;
        while (count <= digit[i])
        {
            j--;
            if (cubie_UD_edge_permutation[j] < i)
                count++;
        }
        cubie_UD_edge_permutation[j] = Edges(i);
    }
}

void cubie_to_UD_edge_permutation(Edges cubie_UD_edge_permutation[], int *UD_edge_permutation)
{
    // gledamo sa desna na levo, radi jednostavnijeg "koda"
    // UD ivice su UR, UF, UL, UB, DR, DF, DL, DB dakle, uzimaju vrednosti iz skupa {0, 1, 2, 3, 4, 5, 6, 7},
    // zato je gotovo identicno kao corner_permutation
    int digit[8], base[8], res = 0;
    base[0] = 1;
    for (int i = 1; i < 8; i++)
    {
        digit[i] = 0;
        base[i] = i*base[i - 1];
    }

    for (int i = 1; i < 8; i++)
    {
        int j = 7;
        while (cubie_UD_edge_permutation[j] != i)
        {
            if (cubie_UD_edge_permutation[j] < i)
                digit[i]++;
            j--;
        }
    }

    for (int i = 1; i < 8; i++)
        res += digit[i]*base[i];

    *UD_edge_permutation = res;
}
