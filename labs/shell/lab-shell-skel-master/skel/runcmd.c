#include "runcmd.h"

int status = 0;
struct cmd* parsed_pipe;
struct backcmd* last_background_cmd;

// runs the command in 'cmd'
int run_cmd(char* cmd) {

	pid_t p;
	struct cmd *parsed;

	// if the "enter" key is pressed
	// just print the promt again
	if (cmd[0] == END_STRING)
		return 0;

	// cd built-in call
	if (cd(cmd)) {
		exec_cd(cmd);
		return 0;
	}

	// exit built-in call
	if (exit_shell(cmd))
		exit(EXIT_SUCCESS);

	// pwd buil-in call
	if (pwd(cmd)) {
		exec_pwd();
		return 0;
	}

	// parses the command line
	parsed = parse_line(cmd);

	// forks and run the command
	if ((p = fork()) == 0) {

		// keep a reference
		// to the parsed pipe cmd
		// so it can be freed later
		if (parsed->type == PIPE)
			parsed_pipe = parsed;

		exec_cmd(parsed);
	}

	// store the pid of the process
	parsed->pid = p;

	// background process special treatment
	if (parsed->type == BACK) {
		print_back_info(parsed);
		last_background_cmd = malloc(sizeof(struct backcmd));
		memcpy(last_background_cmd, parsed, sizeof(struct backcmd));
		free_command(parsed);
		return 0;
	} else {
		waitpid(p, &status, 0);
	}

	print_back_finish_info();
	print_status_info(parsed);

	free_command(parsed);

	return 0;
}
