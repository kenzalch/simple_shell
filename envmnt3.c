#include "main.h"

/**
 * get_environ - Get the value of an environment variable.
 * @envname: Name of the environment variable.
 * @_env: Array of environment variables.
 *
 * Return: A pointer to the value of the environment variable
 *         if it is found.
 *         NULL if the environment variable is not found.
 */
char *get_environ(const char *envname, char **_env)
{
	char *p_env;
	int j, mv;

	/* Initialize p_env value */
	p_env = NULL;
	mv = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (j = 0; _env[j]; j++)
	{
		/* If name and env are equal */
		mv = compare_envname(_env[j], envname);
		if (mv)
		{
			p_env = _env[j];
			break;
		}
	}

	return (p_env + mv);
}

/**
 * display_env - Print the environment variables.
 * @data_sh: Pointer to the data structure containing the
 *           environment variables.
 *
 * Return: 1 on success.
 */
int display_env(shll_comm *data_sh)
{
	int le, n;

	for (le = 0; data_sh->_env[le]; le++)
	{

		for (n = 0; data_sh->_env[le][n]; n++)
			;

		write(STDOUT_FILENO, data_sh->_env[le], n);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_sh->stat = 0;

	return (1);
}

/**
 * _getline - Read input from stream
 * @lnptr: Pointer to the buffer that stores the input
 * @num: Pointer to the size of lnptr
 * @filestream: Stream to read from
 *
 * Return: The number of bytes
 */
ssize_t _getline(char **lnptr, size_t *num, FILE *filestream)
{
	int idx;
	static ssize_t ip;
	ssize_t rval;
	char *buf;
	char t = 'z';

	if (ip == 0)
		fflush(filestream);
	else
		return (-1);
	ip = 0;

	buf = malloc(sizeof(char) * BUFSIZE);
	if (buf == 0)
		return (-1);
	while (t != '\n')
	{
		idx = read(STDIN_FILENO, &t, 1);
		if (idx == -1 || (idx == 0 && ip == 0))
		{
			free(buf);
			return (-1);
		}
		if (idx == 0 && ip != 0)
		{
			ip++;
			break;
		}
		if (ip >= BUFSIZE)
			buf = _realloc(buf, ip, ip + 1);
		buf[ip] = t;
		ip++;
	}
	buf[ip] = '\0';
	get_ln(lnptr, num, buf, ip);
	rval = ip;
	if (idx != 0)
		ip = 0;
	return (rval);
}
