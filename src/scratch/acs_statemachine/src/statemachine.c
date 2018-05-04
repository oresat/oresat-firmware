#include "statemachine.h"

int off_state(void){

	return 0;
}

int ready_state(void){
	
	return 0;
}

int rw_state(void){

	return 0;
}

int mtqr_state(void){

	return 0;
}

int (* state[])() = {off_state,ready_state,rw_state,mtqr_state};

transition state_transitions[] = {
	{RDY,		repeat,		RDY},
	{RDY, 	rw,				RW},
	{RDY, 	mtqr,			MTQR},
	{RDY, 	off,			OFF},
	{RW, 		repeat,		RW},
	{RW, 		rdy,			RDY},
	{MTQR, 	repeat,		MTQR},
	{MTQR, 	rdy,			RDY}
};

int lookup_transitions(state_codes sc,ret_codes rc){
	UNUSED(sc);
	UNUSED(rc);

	return EXIT_SUCCESS;
}






