#include "handlers.h"

char back_msg[BUFLEN];

void background_handler(int signum) {
	if (last_background_cmd == NULL)
		return;
	pid_t exited_pid = wait(NULL);
    if (exited_pid != last_background_cmd->pid)
		return;
	snprintf(back_msg, BUFLEN, "==> terminado: PID=%d (%s)", last_background_cmd->pid, last_background_cmd->scmd);
    free(last_background_cmd);
	last_background_cmd = NULL;
}

void set_action_background() {
    struct sigaction act;
    act.sa_handler = background_handler;
    act.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &act, NULL);
}
