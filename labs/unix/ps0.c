#include "ps0.h"

int main() {
	ps0();
	return 0;
}

void ps0() {
	DIR* directory = opendir("/proc");
	struct dirent* entry;
	printf("%5s %s\n", "PID", "COMMAND");
	while ((entry = readdir(directory)) != NULL) {
		if (is_numeric(entry->d_name)) {
			printf("%5s ", entry->d_name);
			print_comm(entry->d_name);
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

void print_comm(char* pid) {
	char comm_path[6 + strlen(pid) + 5]; // "/proc/[pid]/comm"
	memset(comm_path, '\0', 6 + strlen(pid) + 5);
	sprintf(comm_path, "%s%s%s", "/proc/", pid, "/comm");
	print_file(comm_path);
}

void print_file(char* path) {
	int descriptor = open(path, O_RDONLY);
	char buffer[READ_BYTES];
	memset(buffer, '\0', READ_BYTES);
	int leidos;
	while ((leidos = read(descriptor, buffer, READ_BYTES)) > 0) {
		printf("%s", buffer);
		memset(buffer, '\0', READ_BYTES);
	}
	close(descriptor);
}
