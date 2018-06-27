#ifndef EXEC_H
#define EXEC_H

#include "defs.h"
#include "types.h"
#include "freecmd.h"
#include <signal.h>

extern struct backcmd* last_background_cmd;

void background_handler(int signum);

void set_action_background();

#endif // EXEC_H
