#ifndef DEFINITIONS_H
#define DEFINITIONS_H

enum Corners : int { URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB };
enum Edges : int { UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR };

struct CubieLevelCube
{
    // kocka zadata u "zamenjen sa" kordinatama
    Corners corner_permutation[8];
    int corner_orientation[8];
    Edges edge_permutation[12];
    int edge_orientation[12];
};

struct CordinateLevelCube
{
    int corner_orientation;     // 0, 1, ..., 3^7-1 (ukupno 2187)
    int corner_permutation;     // 0, 1, ..., 8!-1 (ukupno 40320)
    int edge_orientation;       // 0, 1, ..., 2^11-1 (ukupno 2048)
    int UDslice_edge_position;      // 0, 1, ..., (12 nad 4)-1 (ukupno 495)
    int UDslice_edge_permutation;   // 0, 1, ..., 4!-1 (ukupno 24) 
    int UD_edge_permutation;// 0, 1, ..., 8!-1 (ukupno 40320)
};

void input(CubieLevelCube *cube);

// corner_orientation
void corner_orientation_to_cubie(int corner_orientation, int cubie_corner_orientation[]);
void cubie_to_corner_orientation(int cubie_corner_orientation[], int *corner_orientation);

// edge_orientation
void edge_orientation_to_cubie(int edge_orientation, int cubie_edge_orientation[]);
void cubie_to_edge_orientation(int cubie_edge_orientation[], int *edge_orientation);

// UDslice_edge_postition
void UDslice_edge_position_to_cubie(int UDslice_edge_position, Edges cubie_UDslice_edge_position[]);
void cubie_to_UDslice_edge_position(Edges cubie_UDslice_edge_postition[], int *UDslice_edge_position);

// corner_permutation

// UDslice_edge_permutation

// UD_edge_permutation

#endif // DEFINITIONs_H