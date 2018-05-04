#include "statemachine.h"

int main(int argc, char *argv[]) {
	UNUSED(argc);
	UNUSED(argv);
	state_codes cur_state = ENTRY_STATE;
	ret_codes rc;
	int (* state_fun)(void);

	for(;;){
		state_fun = state[cur_state];
		rc = state_fun();
		if (EXIT_STATE == cur_state)
				break;
		cur_state = lookup_transitions(cur_state, rc);
	}

	return EXIT_SUCCESS;
}
