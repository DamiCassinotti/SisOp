#include "ps1.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int main() {
	ps0();
	return 0;
}

void ps0() {
	DIR* directory = opendir("/proc");
	struct dirent* entry;
	printf("%5s %-16s %5s %5s %5s %6s\n", "PID", "COMMAND", "STATE", "PPID", "GROUP", "SESSION");
	while ((entry = readdir(directory)) != NULL) {
		if (is_numeric(entry->d_name)) {
			print_stat(entry->d_name);
		}
	}
	closedir(directory);
}

int is_numeric(char* str) {
	int i = 0;
	while (str[i]) {
		if (!isdigit(str[i]))
			return 0;
		i++;
	}
	return 1;
}

void print_stat(char* process) {
	char comm_path[6 + strlen(process) + 5]; // "/proc/[pid]/comm"
	memset(comm_path, '\0', 6 + strlen(process) + 5);
	sprintf(comm_path, "%s%s%s", "/proc/", process, "/stat");
	print_line(comm_path);
}

void print_line(char* comm_path) {
	int pid, ppid, pgrp, session;
	char comm[16], state;
	FILE* file = fopen(comm_path, "r");
	fscanf(file, "%d %*[(]%[^)]%*[)] %c %d %d %d", &pid, comm, &state, &ppid, &pgrp, &session);
	fclose(file);
	printf("%5d %-16s %5c %5d %5d %6d\n", pid, comm, state, ppid, pgrp, session);
}
