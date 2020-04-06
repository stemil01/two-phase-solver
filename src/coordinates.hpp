#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#define NUM_CORNER_ORIENTATION              2187
#define NUM_EDGE_ORIENTATION                2048 
#define NUM_UDSLICE_EDGE_POSITION           495
#define NUM_CORNER_PERMUTATION              40320
#define NUM_UDSLICE_EDGE_PERMUTATION        24
#define NUM_UD_EDGE_PERMUTATION             40320

#define NUM_PHASE1_PRUNING_TABLE            554273280   // ukupan broj razlicitih kombinacija u prvoj fazi je 2217093120 
                                                        // ovo je 1/4 zato sto u svakoj cuvamo po 4 vrednosti (svaka ima po 2 bita)
                                                        // cuvamo ih s desna na levo u jednom byte-u
#define NUM_PHASE2_CORNER_UD_EDGE           1625702400
#define NUM_PHASE2_CORNER_UDSLICE_EDGE      967680
#define NUM_PHASE2_UD_EDGE_UDSLICE_EDGE     967680


#define SUCCESS_TEXT                    "\033[32m"
#define ERROR_TEXT                      "\033[31m"
#define BOLD_TEXT                       "\033[1m"
#define RESET_TEXT                      "\033[0m"

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
    int corner_orientation;         // 0, 1, ..., 3^7-1 (ukupno 2187)
    int edge_orientation;           // 0, 1, ..., 2^11-1 (ukupno 2048)
    int UDslice_edge_position;      // 0, 1, ..., (12 nad 4)-1 (ukupno 495)
    int corner_permutation;         // 0, 1, ..., 8!-1 (ukupno 40320)
    int UDslice_edge_permutation;   // 0, 1, ..., 4!-1 (ukupno 24) 
    int UD_edge_permutation;        // 0, 1, ..., 8!-1 (ukupno 40320)
};

void input(CubieLevelCube *cube);

// corner_orientation
void corner_orientation_to_cubie(int corner_orientation, int cubie_corner_orientation[]);
void cubie_to_corner_orientation(int cubie_corner_orientation[], int *corner_orientation);

// edge_orientation
void edge_orientation_to_cubie(int edge_orientation, int cubie_edge_orientation[]);
void cubie_to_edge_orientation(int cubie_edge_orientation[], int *edge_orientation);

// UDslice_edge_postition
void UDslice_edge_position_to_cubie(int UDslice_edge_position, bool cubie_UDslice_edge_position[]);
void cubie_to_UDslice_edge_position(bool cubie_UDslice_edge_postition[], int *UDslice_edge_position);

// corner_permutation
void corner_permutation_to_cubie(int corner_permutation, Corners cubie_corner_permutation[]);
void cubie_to_corner_permutation(Corners cubie_corner_permutation[], int *corner_permutation);

// UDslice_edge_permutation
void UDslice_edge_permutation_to_cubie(int UDslice_edge_permutation, Edges cubie_UDslice_edge_permutation[]);
void cubie_to_UDslice_edge_permutation(Edges cubie_UDslice_edge_permutation[], int *UDslice_edge_permutation);

// UD_edge_permutation
void UD_edge_permutation_to_cubie(int UD_edge_permutation, Edges cubie_UD_edge_permutation[]);
void cubie_to_UD_edge_permutation(Edges cubie_to_UD_edge_permutation[], int *UD_edge_permutation);

#endif // COORDINATES_HPP