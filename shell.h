#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* buffer readers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* chain commands */
#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_NORM	0
#define CMD_OR		1

/* convert_num */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

/* 1 when using the sys getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - A distinctive singly linked list structure.
 *
 * @num: An integer field within the node.
 * @str: A string field within the node.
 * @next: Pointer to the next node in the list.
 *
 * This structure defines a singly linked list node with a unique
 * combination of an integer field (num) and a string field (str).
 * It also includes a pointer (next) to the next node in the list.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Stores parameters to be passed into a function,
 * enabling a consistent function pointer struct prototype.
 *
 * @arg: A string generated from getline containing arguments.
 * @argv: An array of strings generated from 'arg'.
 * @path: A string representing the current command's path.
 * @argc: The argument count.
 * @line_count: The count of errors.
 * @err_num: The error code for 'exit()' calls.
 * @linecount_flag: If set, count this line of input.
 * @fname: The filename of the program.
 * @env: A linked list serving as a local copy of 'environ'.
 * @environ: A custom-modified copy of 'environ'
 * derived from the 'env' linked list.
 * @history: The history node.
 * @alias: The alias node.
 * @env_changed: Set to 'on' if 'environ' was altered.
 * @status: The return status of the last executed command.
 * @cmd_buf: Address of a pointer to 'cmd_buf'; set if chaining.
 * @cmd_buf_type: The command type (||, &&, ;).
 * @readfd: The file descriptor from which to read line input.
 * @histcount: The count of history line numbers.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Couples a command type and its corresponding function.
 *
 * @type: Builtin command flag.
 * @func: Associated function pointer.
 *
 * This structure pairs a builtin command flag with its corresponding
 * function pointer, facilitating the execution of built-in commands
 * in a command-line shell.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* loop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* locatorsc */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loops.c */
int loophsh(char **);

/* error.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* champ.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* champ1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* ax_its.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* _tokens.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* strt_.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* splits.c */
int bfree(void **);

/* _truth.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* error_1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin1.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin2.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*get_lines.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* input_info.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environment.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* get_environ.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* proc_file.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* link_list1.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* link_list2.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* msgs.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
