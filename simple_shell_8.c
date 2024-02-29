#include "simple_shell.h"

/**
 * clear_info - it initializes info_t struct
 * @information: The struct address
 */
void clear_info(info_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * set_info - it initializes info_t struct
 * @information: The struct address
 * @avc: The argument vector
 */
void set_info(info_t *information, char **avc)
{
	int ai = 0;

	information->fname = avc[0];
	if (information->arg)
	{
		information->argv = strtow(information->arg, " \t");
		if (!information->argv)
		{
			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (ai = 0; information->argv && information->argv[ai]; ai++)
			;
		information->argc = ai;

		replace_alias(information);
		replace_vars(information);
	}
}

/**
 * free_info - it frees info_t struct fields
 * @information: The struct address
 * @alll: is true if freeing all fields
 */
void free_info(info_t *information, int alll)
{
	ffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (alll)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			free_list(&(information->env));
		if (information->history)
			free_list(&(information->history));
		if (information->alias)
			free_list(&(information->alias));
		ffree(information->environ);
		information->environ = NULL;
		bfree((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUF_FLUSH);
	}
}

