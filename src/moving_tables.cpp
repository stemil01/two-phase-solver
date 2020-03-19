#include <iostream>
#include "definitions.hpp"
#include "moves.hpp"
using namespace std;

int move_corner_orientation[NUM_CORNER_ORIENTATION][18];
int move_edge_orientation[NUM_EDGE_ORIENTATION][18];
int move_UDslice_edge_position[NUM_UDSLICE_EDGE_POSITION][18];

int move_corner_permutation[NUM_CORNER_PERMUTATION][18];
int move_UDslice_edge_permutation[NUM_UDSLICE_EDGE_PERMUTATION][18];
int move_UD_edge_permutation[NUM_UD_EDGE_PERMUTATION][18];

int cubie_move_corner_orientation[8][18][3];
int cubie_move_edge_orientation[12][18][2];
int cubie_move_UDslice_edge_position[12][18][2];

int move_corner[18][8];
int move_edge[18][12];

int corner_orient[8][8][3];
int edge_orient[12][12][2];

// PHASE 1
void generate_move_corner_orientation()
{
    for (int i = 0; i < NUM_CORNER_ORIENTATION; i++)
    {
        int cubie_corner_orientation[8], corner_orientation;
        corner_orientation_to_cubie(i, cubie_corner_orientation);

        for (int move = 0; move < 18; move++)
        {
            int moved[8], prev[8];
            for (int k = 0; k < 8; k++)
                prev[k] = cubie_corner_orientation[k];

            for (int j = 0; j < 3; j++)    
            {
                for (int k = 0; k < 8; k++)
                {
                    int replaced_by = move_corner[move][k];
                    moved[k] = corner_orient[replaced_by][k][prev[replaced_by]];
                }
                for (int k = 0; k < 8; k++)
                    prev[k] = moved[k];

                cubie_to_corner_orientation(moved, &corner_orientation);
                move_corner_orientation[i][move + j] = corner_orientation;
            }
        }
    }
}

void generate_move_edge_orientation()
{
    for (int i = 0; i < NUM_EDGE_ORIENTATION; i++)
    {
        int cubie_edge_orientation[8], edge_orientation;
        edge_orientation_to_cubie(i, cubie_edge_orientation);

        for (int move = 0; move < 18; move++)
        {
            int moved[8], prev[8];
            for (int k = 0; k < 8; k++)
                prev[k] = cubie_edge_orientation[k];

            for (int j = 0; j < 3; j++)    
            {
                for (int k = 0; k < 8; k++)
                {
                    int replaced_by = move_edge[move][k];
                    moved[k] = edge_orient[replaced_by][k][prev[replaced_by]];
                }
                for (int k = 0; k < 8; k++)
                    prev[k] = moved[k];

                cubie_to_edge_orientation(moved, &edge_orientation);
                move_edge_orientation[i][move + j] = edge_orientation;
            }
        }
    }
}

void generate_move_UDslice_edge_position()
{
    for (int i = 0; i < NUM_UDSLICE_EDGE_POSITION; i++)
    {
        bool cubie_UDslice_edge_position[12];
        int UDslice_edge_position;
        UDslice_edge_position_to_cubie(i, cubie_UDslice_edge_position);
        for (int move = 0; move < 18; move += 3)
        {
            bool moved[12], prev[12];
            for (int k = 0; k < 12; k++)
                prev[k] = cubie_UDslice_edge_position[k];
            
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 12; k++)
                    moved[k] = prev[move_edge[move][k]];
                for (int k = 0; k < 12; k++)
                    prev[k] = moved[k];
                cubie_to_UDslice_edge_position(moved, &UDslice_edge_position);
                move_UDslice_edge_position[i][move + j] = UDslice_edge_position;
            }
        }
    }
}

// PHASE 2
void generate_move_corner_permutation()
{
    for (int i = 0; i < NUM_CORNER_PERMUTATION; i++)
    {
        Corners cubie_corner_permutation[8];
        int corner_permutation;
        corner_permutation_to_cubie(i, cubie_corner_permutation);
        for (int move = 0; move < 18; move += 3)
        {
            Corners moved[8], prev[8];
            for (int k = 0; k < 8; k++)
                prev[k] = cubie_corner_permutation[k];
            
            if (move < 12)
            {
                // radi samo phase 2 poteze
                for (int j = 0; j < 2; j++)
                {
                    for (int k = 0; k < 8; k++)
                        moved[k] = prev[move_corner[move][k]];
                    for (int k = 0; k < 8; k++)
                        prev[k] = moved[k]; 
                }
                cubie_to_corner_permutation(moved, &corner_permutation);
                move_corner_permutation[i][move + 1] = corner_permutation;
            }
            else
            {
                // radi sve poteze
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 8; k++)
                        moved[k] = prev[move_corner[move][k]];
                    for (int k = 0; k < 8; k++)
                        prev[k] = moved[k];
                    cubie_to_corner_permutation(moved, &corner_permutation);
                    move_corner_permutation[i][move + j] = corner_permutation;
                }
            }
        }
    }
}

void generate_move_UD_edge_permutation()
{
    for (int i = 0; i < NUM_UD_EDGE_PERMUTATION; i++)
    {
        Edges cubie_UD_edge_permutation[8];
        int UD_edge_permutation;
        UD_edge_permutation_to_cubie(i, cubie_UD_edge_permutation);
        for (int move = 0; move < 18; move += 3)
        {
            Edges moved[8], prev[8];
            for (int k = 0; k < 8; k++)
                prev[k] = cubie_UD_edge_permutation[k];

            if (move < 12)
            {
                // radi samo phase 2 poteze
                for (int j = 0; j < 2; j++)
                {
                    for (int k = 0; k < 8; k++)
                        moved[k] = prev[move_edge[move][k]];
                    for (int k = 0; k < 8; k++)
                        prev[k] = moved[k]; 
                }
                cubie_to_UD_edge_permutation(moved, &UD_edge_permutation);
                move_UD_edge_permutation[i][move + 1] = UD_edge_permutation;
            }
            else
            {
                // radi sve poteze
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 8; k++)
                        moved[k] = prev[move_edge[move][k]];
                    for (int k = 0; k < 8; k++)
                        prev[k] = moved[k];
                    cubie_to_UD_edge_permutation(moved, &UD_edge_permutation);
                    move_UD_edge_permutation[i][move + j] = UD_edge_permutation;
                }
            }
        }
    }
}

void generate_move_UDslice_edge_permutation()
{
    for (int i = 0; i < NUM_UDSLICE_EDGE_PERMUTATION; i++)
    {
        Edges cubie_UDslice_edge_permutation[4];
        int UDslice_edge_permutation;
        UDslice_edge_permutation_to_cubie(i, cubie_UDslice_edge_permutation);
        for (int move = 0; move < 18; move += 3)
        {
            Edges moved[4], prev[4];
            for (int k = 0; k < 4; k++)
                prev[k] = cubie_UDslice_edge_permutation[k];

            if (move < 12)
            {
                // radi samo phase 2 poteze
                for (int j = 0; j < 2; j++)
                {
                    for (int k = 0; k < 4; k++)
                        moved[k] = prev[move_edge[move][k]];
                    for (int k = 0; k < 4; k++)
                        prev[k] = moved[k]; 
                }
                cubie_to_UDslice_edge_permutation(moved, &UDslice_edge_permutation);
                move_UDslice_edge_permutation[i][move + 1] = UDslice_edge_permutation;
            }
            else
            {
                // radi sve poteze
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 4; k++)
                        moved[k] = prev[move_edge[move][k]];
                    for (int k = 0; k < 4; k++)
                        prev[k] = moved[k];
                    cubie_to_UDslice_edge_permutation(moved, &UDslice_edge_permutation);
                    move_UDslice_edge_permutation[i][move + j] = UDslice_edge_permutation;
                }
            }
        }
    }
}
