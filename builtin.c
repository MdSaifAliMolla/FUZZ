#include "fuzz.h"

int fuzz_echo(char **args){
    int start =1;
    bool newline=true;

    if(!args || !args[0])return 1;

    if(args[1] && !strcmp(args[1],"-n")){
        newline=false;
        start=2;
    }
    for(int i=start;args[i];i++){
        p("%s",args[i]);
        if(args[i+1])p(" ");
    }

    if (newline)
		p("\n");

	return (0);
}

int	fuzz_env(char **args)
{
	extern char	**environ;

	(void)args;
	if (!environ)
		return (1);
	for (int i = 0; environ[i]; i++)
		p("%s\n", environ[i]);
	return (0);
}


int	fuzz_exit(char **args)
{
	(void)args;
	dbzSpinnerLoading();
	exit(EX_OK);
} 

int fuzz_uwu(char **args)
{
    (void)args;
    printmeme();
    return 0;
}

int fuzz_help(char **args)
{
    (void)args;
    printhelp();
    return 0;
}

int fuzz_whoami(char **argv) {
    (void)argv; 

    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (!pw) {
        perror("whoami");
        return 1;
    }

    printf("%s\n", pw->pw_name);
    return 0;
}

int fuzz_ls(char **argv){
    const char *path=".";

    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
    struct stat fileStat;
    if (stat(entry->d_name, &fileStat) == -1) {
        perror("stat failed");
        continue;
    }
    printf(Y"%-20s %10lld bytes  %o\n", 
           entry->d_name, 
           (long long)fileStat.st_size, 
           (unsigned int)fileStat.st_mode);
}

    closedir(dir);
    return 0;
}

int fuzz_cd(char **args)
{
    // args[0] = "cd"
    // args[1] = path (may be NULL)
    Chdir(args[1]);
    return 0;
}

int fuzz_pwd(char **args){
    (void)args;
    char cwd[BUFSIZ];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd failed");
    return 0;
}

int fuzz_history(char **args){
    (void)args;
    print_history();
    return 0;
}