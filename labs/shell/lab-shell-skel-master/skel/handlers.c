#include "handlers.h"

char back_msg[BUFLEN];

void background_handler(int signum, siginfo_t* info, void* context) {
    if (info->si_pid != last_background_cmd->pid)
		return;
    if (last_background_cmd == NULL)
		return;
	snprintf(back_msg, BUFLEN, "==> terminado: PID=%d (%s)\n", last_background_cmd->pid, last_background_cmd->scmd);
    last_background_cmd = NULL;
}

void set_action_background() {
    struct sigaction act;
    act.sa_sigaction = background_handler;
    act.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &act, NULL);
}
