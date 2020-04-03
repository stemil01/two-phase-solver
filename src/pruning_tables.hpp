#ifndef PRUNING_TABLES_HPP
#define PRUNING_TABLES_HPP

extern char phase1_pruning[NUM_PHASE1_PRUNING_TABLE];

// ovo ce mozda trebati, OBRISATI AKO SE NE KORISTE KASNIJE
int get_phase1_pruning_value(unsigned int state);
void set_phase1_value(unsigned int state, int value);

unsigned int get_phase1_state(int corner_orientation, int edge_orientation, int UDslice_edge_position);
void get_phase1_coordinates(unsigned int state, int* corner_orientation, int* edge_orientation, int* UDslice_edge_position);

void initialize_phase1_pruning();

void generate_phase1_pruning_table();

#endif // PRUNING_TABLES_HPP