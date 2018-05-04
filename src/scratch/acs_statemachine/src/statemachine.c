

int entry_state(void);
int foo_state(void);
int bar_state(void);
int exit_state(void);

/* array and enum below must be in sync! */
int (* state)(void)[] = { entry_state, foo_state, bar_state, exit_state};
enum state_codes { entry = 0, foo, bar, end};

enum ret_codes { ok, fail, repeat};
struct transition {
    enum state_codes src_state;
    enum ret_codes   ret_code;
    enum state_codes dst_state;
};

/* transitions from end state aren't needed */
struct transition state_transitions[] = {
	{entry, ok,     foo},
	{entry, fail,   end},
	{foo,   ok,     bar},
	{foo,   fail,   end},
	{foo,   repeat, foo},
	{bar,   ok,     end},
	{bar,   fail,   end},
	{bar,   repeat, foo}
};

#define EXIT_STATE end
#define ENTRY_STATE entry

int lookup_transitions(enum state_codes sc){

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	enum state_codes cur_state = ENTRY_STATE;
	enum ret_codes rc;
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

/*
I don't put lookup_transition() function as it is trivial.
That's the way I do state machines for years.
*/
