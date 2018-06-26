#ifndef PRINTSTATUS_H
#define PRINTSTATUS_H

#include "defs.h"
#include "types.h"

extern int status;

extern char back_msg[BUFLEN];

void print_status_info(struct cmd* cmd);

void print_back_info(struct cmd* back);

void print_back_finish_info();

#endif // PRINTSTATUS_H
