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
static int open_redir_fd(char* file) {
	int fd = open(file, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	if (fd < 0) {
		char buf[BUFLEN] = {0};
		snprintf(buf, sizeof buf, "cannot open %s", file);
		perror(buf);
	}
	return fd;
}

void spawn_command(struct execcmd* cmd) {
	set_environ_vars(cmd->eargv, cmd->eargc);
	int result = execvp(cmd->argv[0], cmd->argv);
	if (result < 0) {
		char buf[BUFLEN] = {0};
		snprintf(buf, sizeof buf, "error executing %s", cmd->scmd);
		perror(buf);
	}
}

void spawn_background_command(struct backcmd* cmd) {
	exec_cmd(cmd->c);
}

void spawn_redir_command(struct execcmd* cmd) {
	if (strlen(cmd->in_file) > 0)
		dup2(open_redir_fd(cmd->in_file), STDIN_FILENO);
	if (strlen(cmd->out_file) > 0)
		dup2(open_redir_fd(cmd->out_file), STDOUT_FILENO);
	if (strlen(cmd->err_file) > 0) {
		if (cmd->err_file[0] == '&')
			dup2(atoi(&cmd->err_file[1]), STDERR_FILENO);
		else
			dup2(open_redir_fd(cmd->err_file), STDERR_FILENO);
	}
	spawn_command(cmd);
}

void spawn_pipe_command(struct pipecmd* cmd) {
	int pipefd[2];
	int result = pipe(pipefd);
	if (result < 0) {
		char buf[BUFLEN] = {0};
		snprintf(buf, sizeof buf, "error piping commands %s", cmd->scmd);
		perror(buf);
		return;
	}
	pid_t pid_a, pid_b;
	if ((pid_a = fork()) == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_cmd(cmd->leftcmd);
	} else if ((pid_b = fork()) == 0) {
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		exec_cmd(cmd->rightcmd);
	} else {
		close(pipefd[0]);
		close(pipefd[1]);
	}
	waitpid(pid_a, NULL, 0);
	waitpid(pid_b, NULL, 0);
}

// executes a command - does not return
void exec_cmd(struct cmd* cmd) {

	switch (cmd->type) {

		case EXEC: {
			spawn_command((struct execcmd*)cmd);
			break;
		}

		case BACK: {
			spawn_background_command((struct backcmd*)cmd);
			break;
		}

		case REDIR: {
			spawn_redir_command((struct execcmd*)cmd);
			break;
		}

		case PIPE: {
			spawn_pipe_command((struct pipecmd*)cmd);
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
