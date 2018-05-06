#include "statemachine.h"

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	ACS acs;
	acs_statemachine(&acs);
	
	return EXIT_SUCCESS;
}
