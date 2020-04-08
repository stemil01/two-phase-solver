#ifndef PRUNING_TABLES_HPP
#define PRUNING_TABLES_HPP

extern char phase1_pruning[NUM_PHASE1_PRUNING_TABLE];
extern unsigned char phase2_corner_UD_edge[NUM_PHASE2_CORNER_UD_EDGE];
extern unsigned char phase2_corner_UDslice_edge[NUM_PHASE2_CORNER_UDSLICE_EDGE];
extern unsigned char phase2_UD_edge_UDslice_edge[NUM_PHASE2_UD_EDGE_UDSLICE_EDGE];

int get_phase1_pruning_value(unsigned int state);
void set_phase1_value(unsigned int state, int value);

unsigned char get_phase2_pruning_value(int corner_permutation, int UD_edge_permutation, int UDslice_edge_permutation);

unsigned int get_phase1_state(int corner_orientation, int edge_orientation, int UDslice_edge_position);
void get_phase1_coordinates(unsigned int state, int* corner_orientation, int* edge_orientation, int* UDslice_edge_position);

// PHASE 1
void initialize_phase1_pruning();
void load_phase1_pruning_table();
void generate_phase1_pruning_table();

// PHASE 2
void inititalize_phase2_corner_UD_edge();
void load_phase2_corner_UD_edge();
void generate_phase2_corner_UD_edge();
void initialize_phase2_corner_UDslice_edge();
void load_phase2_corner_UDslice_edge();
void generate_phase2_corner_UDslice_edge();
void initialize_phase2_UD_edge_UDslice_edge();
void load_phase2_UD_edge_UDslice_edge();
void generate_phase2_UD_edge_UDslice_edge();

void generate_phase2_pruning_tables();

#endif // PRUNING_TABLES_HPP