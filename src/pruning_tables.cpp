#include <iostream>
#include <fstream>
#include <queue>
#include "coordinates.hpp"
#include "moves.hpp"
using namespace std;

unsigned char phase1_pruning[NUM_PHASE1_PRUNING_TABLE]; 

int get_phase1_pruning_value(unsigned int state)
{
    int index = state >> 2;
    int position = state & 3;
    int mask = 3 << 2 * position;

    return (phase1_pruning[index] & mask) >> 2 * position;
}

void set_phase1_value(unsigned int state, int value)
{
    int index = state >> 2;
    int position = state & 3;
    value <<= 2 * position;
    value |= ~(3 << 2 * position);
    
    phase1_pruning[index] &= value;
}

unsigned int get_phase1_state(int corner_orientation, int edge_orientation, int UDslice_edge_position)
{
    unsigned int A = NUM_EDGE_ORIENTATION * NUM_UDSLICE_EDGE_POSITION;
    unsigned int B = NUM_UDSLICE_EDGE_POSITION;
    return (unsigned int)corner_orientation * A + (unsigned int)edge_orientation * B + (unsigned int)UDslice_edge_position;
}

void get_phase1_coordinates(unsigned int state, int* corner_orientation, int* edge_orientation, int* UDslice_edge_position)
{
    *UDslice_edge_position = state % NUM_UDSLICE_EDGE_POSITION;
    state /= NUM_UDSLICE_EDGE_POSITION;
    *edge_orientation = state % NUM_EDGE_ORIENTATION;
    state /= NUM_EDGE_ORIENTATION;
    *corner_orientation = state;
}

void initialize_phase1_pruning()
{
    for (int i = 0; i < NUM_PHASE1_PRUNING_TABLE; i++)
        phase1_pruning[i] = ~0;
}

void load_phase1_pruning_table()
{
    ifstream file;
    file.open("resources/pruning_tables/phase1_pruning");
    if (file)
    {
        int temp;
        for (int i = 0; i < NUM_PHASE1_PRUNING_TABLE; i++)
        {
            file >> temp;
            phase1_pruning[i] = temp;
        }
        cout << SUCCESS_TEXT << "phase1_pruning loaded successfully" << RESET_TEXT << '\n';
    }
    else
        cout << ERROR_TEXT << "loading phase1_pruning failed" << RESET_TEXT << '\n';
    file.close();
}

void generate_phase1_pruning_table()
{
    initialize_phase1_pruning();

    bool generate = false;

    char answer;
    cout << "Do you want to generate new " << BOLD_TEXT << "phase1_pruning" << RESET_TEXT << " table? [y/N] ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
    {
        cout << "Are you sure (this operation will take lot of time and memory)? [y/N] ";  
        cin >> answer;
        if (answer == 'Y' || answer == 'y')
            generate = true;
    }

    if (generate)
    {
        queue<unsigned int> q;    
        q.push(0);

        phase1_pruning[0] &= (~0 << 2); // postavljanje da je vrednost stanja 0, jednaka 0

        unsigned int counter = 0;

        while (!q.empty())
        {
            unsigned int state = q.front();
            q.pop();

            counter++;
            unsigned int size = q.size();
            if (counter % 10000000 == 0)
                cout << "q ima " << size << " elemenata; a obelezeno je " << counter << " elemenata" << '\n';

            int corner_orientation, edge_orientation, UDslice_edge_position;
            get_phase1_coordinates(state, &corner_orientation, &edge_orientation, &UDslice_edge_position);
            int index = state >> 2;
            int position = state & 3;
            int mask = 3 << 2 * position;
            int phase1_pruning_value = (phase1_pruning[index] & mask) >> (2 * position);

            int moved_corner_orientation, moved_edge_orientation, moved_UDslice_edge_position;
            unsigned int moved_state;
            int moved_phase1_pruning_value;

            for (int move = 0; move < 18; move++)
            {
                moved_corner_orientation = move_corner_orientation[corner_orientation][move];
                moved_edge_orientation = move_edge_orientation[edge_orientation][move];
                moved_UDslice_edge_position = move_UDslice_edge_position[UDslice_edge_position][move];

                moved_state = get_phase1_state(moved_corner_orientation, moved_edge_orientation, moved_UDslice_edge_position);

                int moved_index = moved_state >> 2;
                int moved_position = moved_state & 3;
                int moved_mask = 3 << 2 * moved_position;

                if ((phase1_pruning[moved_index] & moved_mask) == moved_mask) // ovo znaci da se nije pojavljivao do sad, tj. da ima vrednost 11
                {
                    moved_phase1_pruning_value = (phase1_pruning_value + 1) % 3;
                    moved_phase1_pruning_value <<= 2 * moved_position;
                    moved_phase1_pruning_value |= (unsigned char)~(3 << 2 * moved_position);
                    phase1_pruning[moved_index] &= moved_phase1_pruning_value; // radice & zato sto je vec tamo vrednost 11 

                    q.push(moved_state);
                }
            }
        }

        cout << SUCCESS_TEXT << "SVI CVOROVI SU PRODJENI I TREBALO BI DA JE SVE U NIZU phase1_pruning" << RESET_TEXT << '\n';

        ofstream file;
        file.open("resources/pruning_tables/phase1_pruning");
        if (file)
            for (int i = 0; i < NUM_PHASE1_PRUNING_TABLE; i++)
                file << (int)phase1_pruning[i] << '\n';     // PROVERI DA LI MOZE DA UCITA KARAKTERE TOG OBLIKA, AKO NE, TREBA KORISTITI (INT) ISPRED
                                                            // STO IMA ZA POSLEDICU DUPLO VECU ISKORISCENOST MEMEORIJE
        else
            cout << ERROR_TEXT << "failed writing phase1_pruning" << RESET_TEXT << '\n';
        file.close();
    }
    else
        load_phase1_pruning_table();
}
