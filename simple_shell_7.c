#include "simple_shell.h"

/**
 * get_environ - returns the string array copy of the environ
 * @information: The Structure containing potential arguments.
 *
 * Return: Always 0
 */
char **get_environ(info_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = list_to_strings(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}

/**
 * _unsetenv - Remove the environment variable
 * @information: The Structure containing potential arguments.
 *
 *  Return: 1 on delete or 0 otherwise
 * @varz: the string env variable property
 */
int _unsetenv(info_t *information, char *varz)
{
	list_t *nodez = information->env;
	size_t ai = 0;
	char *pp;

	if (!nodez || !varz)
		return (0);

	while (nodez)
	{
		pp = starts_with(nodez->str, varz);
		if (pp && *pp == '=')
		{
			information->env_changed = delete_node_at_index(&(information->env), ai);
			ai = 0;
			nodez = information->env;
			continue;
		}
		nodez = nodez->next;
		ai++;
	}
	return (information->env_changed);
}

/**
 * _setenv - It Initialize a new environment variable,
 *             or modify an existing one
 * @information: The Structure containing potential arguments.
 *
 * @varz: the string env variable property
 * @valuez: the string env variable value
 *  Return: Always 0
 */
int _setenv(info_t *information, char *varz, char *valuez)
{
	char *buff = NULL;
	list_t *nodez;
	char *pp;

	if (!varz || !valuez)
		return (0);

	buff = malloc(_strlen(varz) + _strlen(valuez) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, varz);
	_strcat(buff, "=");
	_strcat(buff, valuez);
	nodez = information->env;
	while (nodez)
	{
		pp = starts_with(nodez->str, varz);
		if (pp && *pp == '=')
		{
			free(nodez->str);
			nodez->str = buff;
			information->env_changed = 1;
			return (0);
		}
		nodez = nodez->next;
	}
	add_node_end(&(information->env), buff, 0);
	free(buff);
	information->env_changed = 1;
	return (0);
}

