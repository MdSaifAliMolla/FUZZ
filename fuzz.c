#include "fuzz.h"
#include <stdio.h>

int status = 0;

t_builtin	g_builtin[] = 
{
	{.builtin_name = "fecho", .foo=fuzz_echo},   
	{.builtin_name = "fenv", .foo=fuzz_env},   
	{.builtin_name = "fexit", .foo=fuzz_exit}, 
	{.builtin_name = "uwu", .foo=fuzz_uwu},
	{.builtin_name = "fwhoami", .foo=fuzz_whoami},
	{.builtin_name = "fls", .foo=fuzz_ls},
	{.builtin_name = "fcd", .foo=fuzz_cd},
	{.builtin_name = "fpwd", .foo=fuzz_pwd},
	{.builtin_name = "help", .foo=fuzz_help},
	{.builtin_name = "history", .foo=fuzz_history},
	{.builtin_name = NULL},             
};


void	fuzz_launch(char **args)
{

	if (Fork() == Junior_bruh)
	{
		//	char *args[] = {"ls", "-l", "-a", NULL};
		//	execvp("ls", args);
		Execvp(args[0], args);
	}
	else
	{
		Wait(&status);
	}
}

void	fuzz_execute(char **args)
{
	int			i;
	const char	*curr_builtin;

	if (!args || !args[0])
		return ;
	i = 0;

	// 1 check if builtin requested
	while ((curr_builtin = g_builtin[i].builtin_name))
	{
		if (!strcmp(args[0], curr_builtin))
		{
			if ((status = (g_builtin[i].foo)(args)))
				p("%s failed\n", curr_builtin);
			
			return ;
		}
		i++;
	}
	
	fuzz_launch(args);
}



// takes input command
char	*fuzz_read_line(void)
{
	char	*line;
	size_t	bufsize;
	char	cwd[BUFSIZ];

	line = NULL;
	bufsize = 0;
	// check if interactive mode 
	if (isatty(fileno(stdin)))
	{
		if (status)
			p("🦠"C"[%s]"RED"[%d]"RST"🦠 > ", 
					Getcwd(cwd, BUFSIZ), 
					status);
		else
			p("🦠"C"[%s]"RST"🦠 > ", 
					Getcwd(cwd, BUFSIZ));
	}

	Getline(&line, &bufsize, stdin);
	return (line);
}



char	**fuzz_split_line(char *line)
{
	size_t			bufsize;
	unsigned long	position;
	char			**tokens;

	bufsize = BUFSIZ;
	position = 0;
	tokens = Malloc(bufsize * sizeof *tokens);

	for (char *token = strtok(line, SPACE); token; token = strtok(NULL, SPACE))
	{
		tokens[position++] = token;	
		if (position >= bufsize)
		{
			bufsize *= 2;
			tokens = Realloc(tokens, bufsize * sizeof *tokens);
		}
	}
	tokens[position] = NULL;
	return (tokens);
}


int main(int ac,char **av){

    printbanner();
	char	*line;
	char	**args;
	
	// READ->EVAL->EXECUTE->LOOP
	while ((line = fuzz_read_line()))
	{
		if (line[0] != '\n' && strlen(line) > 1)
        	add_to_history(line);
			
		args = fuzz_split_line(line);	

		if (args[0] && !strcmp(args[0], "cd"))
			Chdir(args[1]);
		
		fuzz_execute(args);

		free(line);
		free(args);
	

	}
    
    return EXIT_SUCCESS;
}