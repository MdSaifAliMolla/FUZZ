# ifndef FUZZ_H
# define FUZZ_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>
#include <pwd.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

//Ansi color codes
#define Y		"\033[1;33m"
#define G		"\033[1;32m"
#define C 		"\033[1;36m"
#define RED		"\033[1;31m"
#define RST 	"\033[0m"

#define p(...) printf(__VA_ARGS__)
#define ERROR(msg) fprintf(stderr,RED msg RST "\n")
#define SPACE	"\t\n\v\f\r "
#define Junior_bruh	0

enum{
	OK,     
	ERROR   
};

typedef struct s_builtin
{
    const char *builtin_name;
	int (*foo)(char **av);
} t_builtin;


#define MAX_HISTORY 20
#define MAX_COMMAND_LEN 1024
extern char *history[MAX_HISTORY];
extern int history_count;

//Built-in command function prototypes

int	fuzz_echo(char **args);  
int	fuzz_env(char **args); 
int	fuzz_exit(char **args); 
int fuzz_uwu(char **args);
int fuzz_whoami(char **args);
int fuzz_ls(char **args);
int fuzz_cd(char **args);
int fuzz_pwd(char **args);
int fuzz_help(char **args);
int fuzz_history(char **args);

void 	dbzSpinnerLoading();  
void	printbanner(void);  
void 	printmeme(void);  
void    printhelp(void);
void 	print_history(void);
void	add_to_history(char *command);


void	Chdir(const char *path);      
pid_t	Fork(void);                  
void	Execvp(const char *file, char *const argv[]); 
pid_t	Wait(int *status);
pid_t	Waitpid(pid_t pid, int *status, int options);
void	*Malloc(size_t size);        
void	*Realloc(void *ptr, size_t size); 
char	*Getcwd(char *buf, size_t size); 
void	Getline(char **lineptr, size_t *n, FILE *stream); 


#endif
