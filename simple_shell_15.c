#include "simple_shell.h"

/**
 * hsh - The main shell loop
 * @information: the parameter & return info struct
 * @avtr: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *information, char **avtr)
{
	ssize_t br = 0;
	int builtin_retz = 0;

	while (br != -1 && builtin_retz != -2)
	{
		clear_info(information);
		if (interactive(information))
			_puts("Zillahh$ ");
		_eputchar(BUF_FLUSH);
		br = get_input(information);
		if (br != -1)
		{
			set_info(information, avtr);
			builtin_retz = find_builtin(information);
			if (builtin_retz == -1)
				find_cmd(information);
		}
		else if (interactive(information))
			_putchar('\n');
		free_info(information, 0);
	}
	write_history(information);
	free_info(information, 1);
	if (!interactive(information) && information->status)
		exit(information->status);
	if (builtin_retz == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin_retz);
}

/**
 * find_builtin - It finds a builtin command
 * @information: the parameter & return info struct
 *
 * Return:
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 * -1 if builtin not found.
 */
int find_builtin(info_t *information)
{
	int ai, built_in_retz = -1;
	builtin_table builtintblz[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (ai = 0; builtintblz[ai].type; ai++)
		if (_strcmp(information->argv[0], builtintblz[ai].type) == 0)
		{
			information->line_count++;
			built_in_retz = builtintblz[ai].func(information);
			break;
		}
	return (built_in_retz);
}

/**
 * find_cmd - It finds a command in PATH
 * @information: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *information)
{
	char *pathz = NULL;
	int ai, zk;

	information->path = information->argv[0];
	if (information->linecount_flag == 1)
	{
		information->line_count++;
		information->linecount_flag = 0;
	}
	for (ai = 0, zk = 0; information->arg[ai]; ai++)
		if (!is_delim(information->arg[ai], " \t\n"))
			zk++;
	if (!zk)
		return;

	pathz = find_path(information, _getenv(information, "PATH="),
			information->argv[0]);
	if (pathz)
	{
		information->path = pathz;
		fork_cmd(information);
	}
	else
	{
		if ((interactive(information) || _getenv(information, "PATH=")
					|| information->argv[0][0] == '/')
				&& is_cmd(information, information->argv[0]))
			fork_cmd(information);
		else if (*(information->arg) != '\n')
		{
			information->status = 127;
			print_error(information, "not found\n");
		}
	}
}

/**
 * fork_cmd - It forks a an exec thread to run cmd
 * @information: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(information->path, information->argv,
					get_environ(information)) == -1)
		{
			free_info(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				print_error(information, "Permission denied\n");
		}
	}
}

