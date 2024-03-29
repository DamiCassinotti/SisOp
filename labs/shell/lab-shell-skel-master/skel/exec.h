#ifndef EXEC_H
#define EXEC_H

#include "defs.h"
#include "types.h"
#include "utils.h"
#include "freecmd.h"

extern struct cmd* parsed_pipe;

void exec_cmd(struct cmd* c);

void spawn_command(struct execcmd* cmd);

void spawn_background_command(struct backcmd* cmd);

void spawn_redir_command(struct execcmd* cmd);

void spawn_pipe_command(struct pipecmd* cmd);

void exec_cd(char* cmd);

void exec_pwd();

#endif // EXEC_H
