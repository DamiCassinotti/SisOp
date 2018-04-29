#include "builtin.h"

static int starts_with(char* original_str, char* compare_str) {
	if (strncmp(original_str, compare_str, strlen(compare_str)) == 0)
		return 1;
	return 0;
}

// returns true if the 'exit' call
// should be performed
int exit_shell(char* cmd) {
	return starts_with(cmd, "exit");
}

// returns true if "chdir" was performed
// this means that if 'cmd' contains:
// 	$ cd directory (change to 'directory')
// 	$ cd (change to HOME)
// it has to be executed and then return true
int cd(char* cmd) {
	return starts_with(cmd, "cd");
}

// returns true if 'pwd' was invoked
// in the command line
int pwd(char* cmd) {
	return starts_with(cmd, "pwd");
}
