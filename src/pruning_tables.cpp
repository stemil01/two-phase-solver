#include <iostream>
#include <fstream>
#include <queue>
#include "coordinates.hpp"
#include "moves.hpp"
using namespace std;

unsigned char phase1_pruning[NUM_PHASE1_PRUNING_TABLE]; 
unsigned char phase2_corner_UD_edge[NUM_PHASE2_CORNER_UD_EDGE];
unsigned char phase2_corner_UDslice_edge[NUM_PHASE2_CORNER_UDSLICE_EDGE];
unsigned char phase2_UD_edge_UDslice_edge[NUM_PHASE2_UD_EDGE_UDSLICE_EDGE];

// PHASE 1
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
                file << (int)phase1_pruning[i] << '\n';
        else
            cout << ERROR_TEXT << "failed writing phase1_pruning" << RESET_TEXT << '\n';
        file.close();
    }
    else
        load_phase1_pruning_table();
}

// PHASE 2
void inititalize_phase2_corner_UD_edge()
{
    for (int i = 0; i < NUM_PHASE2_CORNER_UD_EDGE; i++)
        phase2_corner_UD_edge[i] = 255;
}

void load_phase2_corner_UD_edge()
{
    ifstream file;
    file.open("resources/pruning_tables/phase2_corner_UD_edge");
    if (file)
    {
        int temp;
        for (int i = 0; i < NUM_PHASE2_CORNER_UD_EDGE; i++)
        {
            file >> temp;
            phase2_corner_UD_edge[i] = temp;
        }
        cout << SUCCESS_TEXT << "phase2_corner_UD_edge loaded successfully" << RESET_TEXT << '\n';
    }
    else
        cout << ERROR_TEXT << "failed loading phase2_corner_UD_edge" << RESET_TEXT << '\n';
    file.close();
}

void generate_phase2_corner_UD_edge()
{
    inititalize_phase2_corner_UD_edge();

    bool generate = false;
    char answer;
    cout << "Do you want to generate new " << BOLD_TEXT << "phase2_corner_UD_edge" << RESET_TEXT << " table? [y/N] ";
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
        queue<int> q;    
        q.push(0);

        phase2_corner_UD_edge[0] = 0; // postavljanje da je vrednost stanja 0, jednaka 0

        int counter = 0;

        while (!q.empty())
        {
            int state = q.front();
            q.pop();

            counter++;
            int size = q.size();
            if (counter % 10000000 == 0)
                cout << "q ima " << size << " elemenata; a obelezeno je " << counter << " elemenata" << '\n';

            int UD_edge_permutation = state % NUM_UD_EDGE_PERMUTATION;
            int corner_permutation = state / NUM_UD_EDGE_PERMUTATION;

            int moved_corner_permutation, moved_UD_edge_permutation;
            int moved_state;

            for (int move = 0; move < 18; move++)
                if (move % 3 == 1 || move >= 12) // ovo znaci da gleda samo phase2 poteze R2, F2, L2, B2 i sve U i D
                {
                    moved_corner_permutation = move_corner_permutation[corner_permutation][move];
                    moved_UD_edge_permutation = move_UD_edge_permutation[UD_edge_permutation][move];

                    moved_state = moved_corner_permutation * NUM_UD_EDGE_PERMUTATION + moved_UD_edge_permutation;

                    if (phase2_corner_UD_edge[moved_state] == 255) // ovo znaci da se nije pojavljivao do sad
                    {
                        phase2_corner_UD_edge[moved_state] = phase2_corner_UD_edge[state] + 1;
                        q.push(moved_state);
                    }
                }
        }

        cout << SUCCESS_TEXT << "SVI CVOROVI SU PRODJENI I TREBALO BI DA JE SVE U NIZU phase2_corner_UD_edge" << RESET_TEXT << '\n';

        ofstream file;
        file.open("resources/pruning_tables/phase2_corner_UD_edge");
        if (file)
            for (int i = 0; i < NUM_PHASE2_CORNER_UD_EDGE; i++)
                file << (int)phase2_corner_UD_edge[i] << '\n';
        else
            cout << ERROR_TEXT << "failed writing phase2_corner_UD_edge" << RESET_TEXT << '\n';
        file.close();
    }
    else
        load_phase2_corner_UD_edge();
    
}

void initialize_phase2_corner_UDslice_edge()
{
    for (int i = 0; i < NUM_PHASE2_CORNER_UDSLICE_EDGE; i++)
        phase2_corner_UDslice_edge[i] = 255;
}

void load_phase2_corner_UDslice_edge()
{
    ifstream file;
    file.open("resources/pruning_tables/phase2_corner_UDslice_edge");
    if (file)
    {
        int temp;
        for (int i = 0; i < NUM_PHASE2_CORNER_UDSLICE_EDGE; i++)
        {
            file >> temp;
            phase2_corner_UDslice_edge[i] = temp;
        }
        cout << SUCCESS_TEXT << "phase2_corner_UDslice_edge loaded successfully" << RESET_TEXT << '\n';
    }
    else
        cout << ERROR_TEXT << "failed loading phase2_corner_UDslice_edge" << RESET_TEXT << '\n';
    file.close();
}

void generate_phase2_corner_UDslice_edge()
{
    initialize_phase2_corner_UDslice_edge();
    phase2_corner_UDslice_edge[0] = 0;
    queue<int> q;
    q.push(0);

    bool generate = false;
    char answer;
    cout << "Do you want to generate new " << BOLD_TEXT << "phase2_corner_UDslice_edge" << RESET_TEXT << " table? [y/N] ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
        generate = true;

    if (generate)
    {
        while (!q.empty())
        {
            int state = q.front();
            q.pop();

            int UDslice_edge_permutaiton = state % NUM_UDSLICE_EDGE_PERMUTATION;
            int corner_permutation = state / NUM_UDSLICE_EDGE_PERMUTATION;

            int moved_corner_permutation, moved_UDslice_edge_permutation;
            int moved_state;
            
            for (int move = 0; move < 18; move++)
                if (move % 3 == 1 || move >= 12)
                {
                    moved_corner_permutation = move_corner_permutation[corner_permutation][move];
                    moved_UDslice_edge_permutation = move_UDslice_edge_permutation[UDslice_edge_permutaiton][move];

                    moved_state = moved_corner_permutation * NUM_UDSLICE_EDGE_PERMUTATION + moved_UDslice_edge_permutation;
                    if (phase2_corner_UDslice_edge[moved_state] == 255) // ako nije vec obidjen
                    {
                        phase2_corner_UDslice_edge[moved_state] = phase2_corner_UDslice_edge[state] + 1;
                        q.push(moved_state);
                    }
                }
        }

        ofstream file;
        file.open("resources/pruning_tables/phase2_corner_UDslice_edge");
        if (file)
            for (int i = 0; i < NUM_PHASE2_CORNER_UDSLICE_EDGE; i++)
                file << (int)phase2_corner_UDslice_edge[i] << '\n';
        else
            cout << ERROR_TEXT << "failed writing phase2_corner_UDslice_edge" << RESET_TEXT << '\n';
    }
    else
        load_phase2_corner_UDslice_edge();
}

void initialize_phase2_UD_edge_UDslice_edge()
{
    for (int i = 0; i < NUM_PHASE2_UD_EDGE_UDSLICE_EDGE; i++)
        phase2_UD_edge_UDslice_edge[i] = 255;
}

void load_phase2_UD_edge_UDslice_edge()
{
    ifstream file;
    file.open("resources/pruning_tables/phase2_UD_edge_UDslice_edge");
    if (file)
    {
        int temp;
        for (int i = 0; i < NUM_PHASE2_UD_EDGE_UDSLICE_EDGE; i++)
        {
            file >> temp;
            phase2_UD_edge_UDslice_edge[i] = temp;
        }
        cout << SUCCESS_TEXT << "phase2_UD_edge_UDslice_edge loaded successfully" << RESET_TEXT << '\n';
    }
    else
        cout << ERROR_TEXT << "failed loading phase2_UD_edge_UDslice_edge" << RESET_TEXT << '\n';
    file.close();
}

void generate_phase2_UD_edge_UDslice_edge()
{
    initialize_phase2_UD_edge_UDslice_edge();
    phase2_UD_edge_UDslice_edge[0] = 0;
    queue<int> q;
    q.push(0);

    bool generate = false;
    char answer;
    cout << "Do you want to generate new " << BOLD_TEXT << "phase2_UD_edge_UDslice_edge" << RESET_TEXT << " table? [y/N] ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
        generate = true;

    if (generate)
    {
        while (!q.empty())
        {
            int state = q.front();
            q.pop();

            int UDslice_edge_permutaiton = state % NUM_UDSLICE_EDGE_PERMUTATION;
            int UD_edge_permutation = state / NUM_UDSLICE_EDGE_PERMUTATION;

            int moved_UD_edge_permutation, moved_UDslice_edge_permutation;
            int moved_state;
            
            for (int move = 0; move < 18; move++)
                if (move % 3 == 1 || move >= 12)
                {
                    moved_UD_edge_permutation = move_UD_edge_permutation[UD_edge_permutation][move];
                    moved_UDslice_edge_permutation = move_UDslice_edge_permutation[UDslice_edge_permutaiton][move];

                    moved_state = moved_UD_edge_permutation * NUM_UDSLICE_EDGE_PERMUTATION + moved_UDslice_edge_permutation;
                    if (phase2_UD_edge_UDslice_edge[moved_state] == 255) // ako nije vec obidjen
                    {
                        phase2_UD_edge_UDslice_edge[moved_state] = phase2_UD_edge_UDslice_edge[state] + 1;
                        q.push(moved_state);
                    }
                }
        }

        ofstream file;
        file.open("resources/pruning_tables/phase2_UD_edge_UDslice_edge");
        if (file)
            for (int i = 0; i < NUM_PHASE2_UD_EDGE_UDSLICE_EDGE; i++)
                file << (int)phase2_UD_edge_UDslice_edge[i] << '\n';
        else
            cout << ERROR_TEXT << "failed writing phase2_UD_edge_UDslice_edge" << RESET_TEXT << '\n';
    }
    else
        load_phase2_UD_edge_UDslice_edge();
}

void generate_phase2_pruning_tables()
{
    generate_phase2_corner_UD_edge();
    generate_phase2_corner_UDslice_edge();
    generate_phase2_UD_edge_UDslice_edge();
}
