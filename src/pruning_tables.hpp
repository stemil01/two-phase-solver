#ifndef PRUNING_TABLES_HPP
#define PRUNING_TABLES_HPP

extern char phase1_pruning[554273280];

unsigned int get_phase1_state(int corner_orientation, int edge_orientation, int UDslice_edge_position);
void get_phase1_coordinates(unsigned int state, int* corner_orientation, int* edge_orientation, int* UDslice_edge_position);

void generate_phase1_pruning_table();

#endif // PRUNING_TABLES_HPP