#include <iostream>
#include <fstream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

// REDOSLED POTEZA
// R R2 R3 F F2 F3 L L2 L3 B B2 B3 U U2 U3 D D2 D3

// MOVING TABLES
int move_corner_orientation[NUM_CORNER_ORIENTATION][18];
int move_edge_orientation[NUM_EDGE_ORIENTATION][18];
int move_UDslice_edge_position[NUM_UDSLICE_EDGE_POSITION][18];

int move_corner_permutation[NUM_CORNER_PERMUTATION][18];
int move_UD_edge_permutation[NUM_UD_EDGE_PERMUTATION][18];
int move_UDslice_edge_permutation[NUM_UDSLICE_EDGE_PERMUTATION][18];

int cubie_move_corner_orientation[8][18][3];
int cubie_move_edge_orientation[12][18][2];
int cubie_move_UDslice_edge_position[12][18][2];

// pomocni nizovi za pravljenje moving table-ova
int move_corner[18][8];
int move_edge[18][12];

int corner_orient[18][8][3];
int edge_orient[18][12][2];

void initialize_move_corner()
{
    for (int move = 0; move < 18; move++)
        for (int corner = 0; corner < 8; corner++)
            move_corner[move][corner] = corner;

    move_corner[R][URF] = DFR;
    move_corner[R][UBR] = URF;
    move_corner[R][DRB] = UBR;
    move_corner[R][DFR] = DRB;

    move_corner[F][URF] = UFL;
    move_corner[F][DFR] = URF;
    move_corner[F][DLF] = DFR;
    move_corner[F][UFL] = DLF;

    move_corner[L][UFL] = ULB;
    move_corner[L][DLF] = UFL;
    move_corner[L][DBL] = DLF;
    move_corner[L][ULB] = DBL;

    move_corner[B][ULB] = UBR;
    move_corner[B][DBL] = ULB;
    move_corner[B][DRB] = DBL;
    move_corner[B][UBR] = DRB;

    move_corner[U][URF] = UBR;
    move_corner[U][UFL] = URF;
    move_corner[U][ULB] = UFL;
    move_corner[U][UBR] = ULB;

    move_corner[D][DFR] = DLF;
    move_corner[D][DRB] = DFR;
    move_corner[D][DBL] = DRB;
    move_corner[D][DLF] = DBL;
}

void initialize_move_edge()
{
    for (int move = 0; move < 18; move++)
        for (int edge = 0; edge < 12; edge++)
            move_edge[move][edge] = edge;
        
    move_edge[R][UR] = FR;
    move_edge[R][BR] = UR;
    move_edge[R][DR] = BR;
    move_edge[R][FR] = DR;

    move_edge[F][UF] = FL;
    move_edge[F][FR] = UF;
    move_edge[F][DF] = FR;
    move_edge[F][FL] = DF;

    move_edge[L][UL] = BL;
    move_edge[L][FL] = UL;
    move_edge[L][DL] = FL;
    move_edge[L][BL] = DL;
    
    move_edge[B][UB] = BR;
    move_edge[B][BL] = UB;
    move_edge[B][DB] = BL;
    move_edge[B][BR] = DB;

    move_edge[U][UR] = UB;
    move_edge[U][UF] = UR;
    move_edge[U][UL] = UF;
    move_edge[U][UB] = UL;

    move_edge[D][DR] = DF;
    move_edge[D][DB] = DR;
    move_edge[D][DL] = DB;
    move_edge[D][DF] = DL;
}

void initialize_corner_orient()
{
    for (int move = 0; move < 18; move++)
        for (int corner = 0; corner < 8; corner++)
            for (int orient = 0; orient < 3; orient++)
                corner_orient[move][corner][orient] = orient;

    // R
    corner_orient[R][URF][0] = 2;
    corner_orient[R][URF][1] = 0;
    corner_orient[R][URF][2] = 1;

    corner_orient[R][UBR][0] = 1;
    corner_orient[R][UBR][1] = 2;
    corner_orient[R][UBR][2] = 0;

    corner_orient[R][DRB][0] = 2;
    corner_orient[R][DRB][1] = 0;
    corner_orient[R][DRB][2] = 1;

    corner_orient[R][DFR][0] = 1;
    corner_orient[R][DFR][1] = 2;
    corner_orient[R][DFR][2] = 0;

    // F
    corner_orient[F][URF][0] = 1;
    corner_orient[F][URF][1] = 2;
    corner_orient[F][URF][2] = 0;

    corner_orient[F][DFR][0] = 2;
    corner_orient[F][DFR][1] = 0;
    corner_orient[F][DFR][2] = 1;

    corner_orient[F][DLF][0] = 1;
    corner_orient[F][DLF][1] = 2;
    corner_orient[F][DLF][2] = 0;

    corner_orient[F][UFL][0] = 2;
    corner_orient[F][UFL][1] = 0;
    corner_orient[F][UFL][2] = 1;
    
    // L
    corner_orient[L][UFL][0] = 1;
    corner_orient[L][UFL][1] = 2;
    corner_orient[L][UFL][2] = 0;

    corner_orient[L][DLF][0] = 2;
    corner_orient[L][DLF][1] = 0;
    corner_orient[L][DLF][2] = 1;

    corner_orient[L][DBL][0] = 1;
    corner_orient[L][DBL][1] = 2;
    corner_orient[L][DBL][2] = 0;

    corner_orient[L][ULB][0] = 2;
    corner_orient[L][ULB][1] = 0;
    corner_orient[L][ULB][2] = 1;

    // B
    corner_orient[B][ULB][0] = 1;
    corner_orient[B][ULB][1] = 2;
    corner_orient[B][ULB][2] = 0;

    corner_orient[B][DBL][0] = 2;
    corner_orient[B][DBL][1] = 0;
    corner_orient[B][DBL][2] = 1;

    corner_orient[B][DRB][0] = 1;
    corner_orient[B][DRB][1] = 2;
    corner_orient[B][DRB][2] = 0;

    corner_orient[B][UBR][0] = 2;
    corner_orient[B][UBR][1] = 0;
    corner_orient[B][UBR][2] = 1;
}

void initialize_edge_orient()
{
    for (int move = 0; move < 18; move++)
        for (int edge = 0; edge < 12; edge++)
            for (int orient = 0; orient < 2; orient++)
                edge_orient[move][edge][orient] = orient;
    
    // F
    edge_orient[F][UF][0] = 1;
    edge_orient[F][UF][1] = 0;

    edge_orient[F][FR][0] = 1;
    edge_orient[F][FR][1] = 0;

    edge_orient[F][DF][0] = 1;
    edge_orient[F][DF][1] = 0;

    edge_orient[F][FL][0] = 1;
    edge_orient[F][FL][1] = 0;

    // B
    edge_orient[B][UB][0] = 1;
    edge_orient[B][UB][1] = 0;

    edge_orient[B][BL][0] = 1;
    edge_orient[B][BL][1] = 0;

    edge_orient[B][DB][0] = 1;
    edge_orient[B][DB][1] = 0;

    edge_orient[B][BR][0] = 1;
    edge_orient[B][BR][1] = 0;
}

// FUNKCIJE ZA UCITAVANJE IZ VEC GENERISANIH FAJLOVA
void load_move_corner_orientation()
{
    ifstream file;
    file.open("../resources/moving_tables/move_corner_orientation");
    if (file) 
    {
        for (int i = 0; i < NUM_CORNER_ORIENTATION; i++)
            for (int move = 0; move < 18; move++)
                file >> move_corner_orientation[i][move];
    
        cout << SUCCESS_COLOR << "move_corner_orienation loaded successfully" << RESET_COLOR << '\n';
    }
    else
        cout << ERROR_COLOR << "failed loading move_corner_orientation file" << RESET_COLOR << '\n';    
    file.close();
}

void load_move_edge_orientation()
{
    ifstream file;
    file.open("../resources/moving_tables/move_edge_orientation");
    if (file) 
    {
        for (int i = 0; i < NUM_EDGE_ORIENTATION; i++)
            for (int move = 0; move < 18; move++)
                file >> move_edge_orientation[i][move];

        cout << SUCCESS_COLOR << "move_edge_orientation loaded successfully" << RESET_COLOR << '\n';
    }
    else
        cout << ERROR_COLOR << "failed loading move_edge_orientation file" << RESET_COLOR << '\n';    
    file.close();
}

void load_move_UDslice_edge_position()
{
    ifstream file;
    file.open("../resources/moving_tables/move_UDslice_edge_position");
    if (file) 
    {
        for (int i = 0; i < NUM_UDSLICE_EDGE_POSITION; i++)
            for (int move = 0; move < 18; move++)
                file >> move_UDslice_edge_position[i][move];
        
        cout << SUCCESS_COLOR << "move_UDslice_edge_position loaded successfully" << RESET_COLOR << '\n';
    }
    else
        cout << ERROR_COLOR << "failed loading move_UDslice_edge_position file" << RESET_COLOR << '\n';    
    file.close();
}

void load_move_corner_permutation()
{
    ifstream file;
    file.open("../resources/moving_tables/move_corner_permutation");
    if (file) 
    {
        for (int i = 0; i < NUM_CORNER_PERMUTATION; i++)
            for (int move = 0; move < 18; move += 3)
            {
                if (move < 12)
                    file >> move_corner_permutation[i][move + 1];
                else
                    for (int j = 0; j < 3; j++)
                        file >> move_corner_permutation[i][move + j];
            }
        
        cout << SUCCESS_COLOR << "move_corner_permutation loaded successfully" << RESET_COLOR << '\n';
    }
    else
        cout << ERROR_COLOR << "failed loading move_corner_permutation file" << RESET_COLOR << '\n';    
    file.close();
}

void load_move_UD_edge_permutation()
{
    ifstream file;
    file.open("../resources/moving_tables/move_UD_edge_permutation");
    if (file) 
    {
        for (int i = 0; i < NUM_UD_EDGE_PERMUTATION; i++)
            for (int move = 0; move < 18; move += 3)
            {
                if (move < 12)
                    file >> move_UD_edge_permutation[i][move + 1];
                else
                    for (int j = 0; j < 3; j++)
                        file >> move_UD_edge_permutation[i][move + j];
            }

        cout << SUCCESS_COLOR << "move_UD_edge_permutation loaded successfully" << RESET_COLOR << '\n';
    }
    else
        cout << ERROR_COLOR << "failed loading move_UD_edge_permutation file" << RESET_COLOR << '\n';    
    file.close();
}

void load_move_UDslice_edge_permutation()
{
    ifstream file;
    file.open("../resources/moving_tables/move_UDslice_edge_permutation");
    if (file) 
    {
        for (int i = 0; i < NUM_UDSLICE_EDGE_PERMUTATION; i++)
            for (int move = 0; move < 18; move += 3)
            {
                if (move < 12)
                    file >> move_UDslice_edge_permutation[i][move + 1];
                else
                    for (int j = 0; j < 3; j++)
                        file >> move_UDslice_edge_permutation[i][move + j];
            }

        cout << SUCCESS_COLOR << "move_UDslice_edge_permutation loaded successfully" << RESET_COLOR << '\n';
    }
    else
        cout << ERROR_COLOR << "failed loading move_UDslice_edge_permutation file" << RESET_COLOR << '\n';    
    file.close();
}

// FUNKCIJE ZA POZIVANJE
void initialize_moves()
{
    initialize_move_corner();
    initialize_move_edge();
    initialize_corner_orient();
    initialize_edge_orient();
}

void generate_moving_tables()
{
    initialize_moves();

    char answer;
    bool generate = true;
    cout << "Do you want to generate new moving tables? [Y/n] ";
    cin >> answer;
    if (answer == 'N' || answer == 'n')
        generate = false;

    if (generate)
    {
        generate_move_corner_orientation();
        generate_move_edge_orientation();
        generate_move_UDslice_edge_position();
        generate_move_corner_permutation();
        generate_move_UD_edge_permutation();
        generate_move_UDslice_edge_permutation();
    }
    else
    {
        load_move_corner_orientation();
        load_move_edge_orientation();
        load_move_UDslice_edge_position();
        load_move_corner_permutation();
        load_move_UD_edge_permutation();
        load_move_UDslice_edge_permutation();
    }
}
