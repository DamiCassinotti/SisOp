#include "exec.h"

// sets the "key" argument with the key part of
// the "arg" argument and null-terminates it
static void get_environ_key(char* arg, char* key) {

	int i;
	for (i = 0; arg[i] != '='; i++)
		key[i] = arg[i];

	key[i] = END_STRING;
}

// sets the "value" argument with the value part of
// the "arg" argument and null-terminates it
static void get_environ_value(char* arg, char* value, int idx) {

	int i, j;
	for (i = (idx + 1), j = 0; i < strlen(arg); i++, j++)
		value[j] = arg[i];

	value[j] = END_STRING;
}

// sets the environment variables passed
// in the command line
//
// Hints:
// - use 'block_contains()' to
// 	get the index where the '=' is
// - 'get_environ_*()' can be useful here
static void set_environ_vars(char** eargv, int eargc) {
	for (int i = 0; i < eargc; i++) {
		char key[ARGSIZE] = {0};
		char value[ARGSIZE] = {0};
		get_environ_key(eargv[i], key);
		get_environ_value(eargv[i], value, strlen(key));
		setenv(key, value, 1);
	}
}

// opens the file in which the stdin/stdout or
// stderr flow will be redirected, and returns
// the file descriptor
//
// Find out what permissions it needs.
// Does it have to be closed after the execve(2) call?
//
// Hints:
// - if O_CREAT is used, add S_IWUSR and S_IRUSR
// 	to make it a readable normal file
static int open_redir_fd(char* file) {

	// Your code here
	return -1;
}

void spawn_command(struct execcmd* cmd) {
	set_environ_vars(cmd->eargv, cmd->eargc);
	execvp(cmd->argv[0], cmd->argv);
}

void spawn_background_command(struct backcmd* cmd) {
	exec_cmd(cmd->c);
}

// executes a command - does not return
//
// Hint:
// - check how the 'cmd' structs are defined
// 	in types.h
void exec_cmd(struct cmd* cmd) {

	switch (cmd->type) {

		case EXEC:
			spawn_command((struct execcmd*)cmd);
			break;

		case BACK: {
			spawn_background_command((struct backcmd*)cmd);
			break;
		}

		case REDIR: {
			// changes the input/output/stderr flow
			//
			// Your code here
			printf("Redirections are not yet implemented\n");
			_exit(-1);
			break;
		}

		case PIPE: {
			// pipes two commands
			//
			// Your code here
			printf("Pipes are not yet implemented\n");

			// free the memory allocated
			// for the pipe tree structure
			free_command(parsed_pipe);

			break;
		}
	}
}

void exec_cd(char* cmd) {
	char* nwd = split_line(cmd, ' ');
	if (chdir(nwd) != 0) {
		char buf[BUFLEN] = {0};
		snprintf(buf, sizeof buf, "cannot cd to %s", nwd);
		perror(buf);
	}
}

void exec_pwd() {
	char* cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}
