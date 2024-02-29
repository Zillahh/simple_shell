#include "simple_shell.h"

/**
 * is_chain - It test if current char in buffer is a chain delimeter
 * @information: the parameter struct
 * @buff: the char buffer
 * @bp: address of current position in buf
 *
 * Return: 1 if chain delimeter or 0 otherwise
 */
int is_chain(info_t *information, char *buff, size_t *bp)
{
	size_t zmj = *bp;

	if (buff[zmj] == '|' && buff[zmj + 1] == '|')
	{
		buff[zmj] = 0;
		zmj++;
		information->cmd_buf_type = CMD_OR;
	}
	else if (buff[zmj] == '&' && buff[zmj + 1] == '&')
	{
		buff[zmj] = 0;
		zmj++;
		information->cmd_buf_type = CMD_AND;
	}
	else if (buff[zmj] == ';') /* found end of this command */
	{
		buff[zmj] = 0; /* replace semicolon with null */
		information->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*bp = zmj;
	return (1);
}

/**
 * check_chain - It checks we should continue chaining based on last status
 * @information: the parameter struct
 * @buff: the char buffer
 * @bp: address of current position in buf
 * @ai: starting position in buf
 * @lenz: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *information, char *buff, size_t *bp,
		size_t ai, size_t lenz)
{
	size_t zmj = *bp;

	if (information->cmd_buf_type == CMD_AND)
	{
		if (information->status)
		{
			buff[ai] = 0;
			zmj = lenz;
		}
	}
	if (information->cmd_buf_type == CMD_OR)
	{
		if (!information->status)
		{
			buff[ai] = 0;
			zmj = lenz;
		}
	}

	*bp = zmj;
}

/**
 * replace_alias - It replaces an aliases in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced or 0 otherwise
 */
int replace_alias(info_t *information)
{
	int ai;
	list_t *nodez;
	char *bp;

	for (ai = 0; ai < 10; ai++)
	{
		nodez = node_starts_with(information->alias, information->argv[0], '=');
		if (!nodez)
			return (0);
		free(information->argv[0]);
		bp = _strchr(nodez->str, '=');
		if (!bp)
			return (0);
		bp = _strdup(bp + 1);
		if (!bp)
			return (0);
		information->argv[0] = bp;
	}
	return (1);
}

/**
 * replace_vars - It replaces vars in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced or 0 otherwise
 */
int replace_vars(info_t *information)
{
	int ai = 0;
	list_t *nodez;

	for (ai = 0; information->argv[ai]; ai++)
	{
		if (information->argv[ai][0] != '$' || !information->argv[ai][1])
			continue;

		if (!_strcmp(information->argv[ai], "$?"))
		{
			replace_string(&(information->argv[ai]),
					_strdup(convert_number(information->status, 10, 0)));
			continue;
		}
		if (!_strcmp(information->argv[ai], "$$"))
		{
			replace_string(&(information->argv[ai]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nodez = node_starts_with(information->env, &information->argv[ai][1], '=');
		if (nodez)
		{
			replace_string(&(information->argv[ai]),
					_strdup(_strchr(nodez->str, '=') + 1));
			continue;
		}
		replace_string(&information->argv[ai], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - It replaces string
 * @oldz: The address of old string
 * @newz: The new string
 *
 * Return: 1 if replaced or 0 otherwise
 */
int replace_string(char **oldz, char *newz)
{
	free(*oldz);
	*oldz = newz;
	return (1);
}

