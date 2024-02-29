#include "simple_shell.h"

/**
 * _myexit - it exits the shell
 * @information: The Structure containing potential arguments.
 *
 * Return: It exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *information)
{
	int exitchecking;

	if (information->argv[1])
	{
		exitchecking = _erratoi(information->argv[1]);
		if (exitchecking == -1)
		{
			information->status = 2;
			print_error(information, "Illegal number identified: ");
			_eputs(information->argv[1]);
			_eputchar('\n');
			return (1);
		}
		information->err_num = _erratoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _mycd - It changes the current directory of the process
 * @information: The Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _mycd(info_t *information)
{
	char *strng, *dirz, buffer[1024];
	int chdir_retz;

	strng = getcwd(buffer, 1024);
	if (!strng)
		_puts("TODO: getcwd failure\n");
	if (!information->argv[1])
	{
		dirz = _getenv(information, "HOME=");
		if (!dirz)
		{
			chdir_retz =
				chdir((dirz = _getenv(information, "PWD=")) ? dirz : "/");
		free(dirz);
		}
		else
			chdir_retz = chdir(dirz);
	}
	else if (_strcmp(information->argv[1], "-") == 0)
	{
		if (!_getenv(information, "OLDPWD="))
		{
			_puts(strng);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(information, "OLDPWD=")), _putchar('\n');
		chdir_retz =
			chdir((dirz = _getenv(information, "OLDPWD=")) ? dirz : "/");
		free(dirz);
	}
	else
		chdir_retz = chdir(information->argv[1]);
	if (chdir_retz == -1)
	{
		print_error(information, "can't cd into ");
		_eputs(information->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(information, "OLDPWD", _getenv(information, "PWD="));
		_setenv(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - It changes the current directory of the process
 * @information: The Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myhelp(info_t *information)
{
	char **arg_arrayz;

	arg_arrayz = information->argv;
	_puts("help call works. Function not implemented \n");
	if (0)
		_puts(*arg_arrayz);
	return (0);
}

