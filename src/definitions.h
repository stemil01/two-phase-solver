#ifndef CUBE_H
#define CUBE_H

enum Corners : char { URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB };
enum Edges : char { UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR };

struct Cubie
{
    char replaced_by, orientation;  
};

struct CubieLevelCube
{
    // kocka zadata u "zamenjen sa" kordinatama
    Cubie cubie[20];
};

struct CordinateLevelCube
{
    int corner_orientation;     // 0, 1, ..., 3^7-1 (ukupno 2187)
    int corner_permutation;     // 0, 1, ..., 8!-1 (ukupno 40320)
    int edge_orientation;       // 0, 1, ..., 2^11-1 (ukupno 2048)
    int UD_edges_position;      // 0, 1, ..., (12 nad 4) - 1 (ukupno 495)
    int UD_edges_permutation;   // 0, 1, ..., 4!-1 (ukupno 24) 
    int nonUD_edges_permutation;// 0, 1, ..., 8!-1 (ukupno 40320)
};

void input(CubieLevelCube *cube);

#endif // CUBE_H