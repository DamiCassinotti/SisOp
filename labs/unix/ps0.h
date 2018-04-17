#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define READ_BYTES 1024

int main();
void ps0();
int is_numeric(char* str);
void print_comm(char* pid);
void print_file(char* path);
