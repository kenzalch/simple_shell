#include "main.h"
/**
 * error_404 - generates a generic error message for "command not found".
 * @data_sh: data relevant to the shell (counter, arguments).
 *
 * Return: The error message.
 */
char *error_404(shll_comm *data_sh)
{
	char *errr, *vtr;
	int lgth;

	vtr = conv_itoa(data_sh->counter);
	lgth = _strlen(data_sh->argv[0]) + _strlen(vtr);
	lgth += _strlen(data_sh->args[0]) + 16;
	errr = malloc(sizeof(char) * (lgth + 1));
	if (errr == 0)
	{
		free(errr);
		free(vtr);
		return (NULL);
	}
	_strcpy(errr, data_sh->argv[0]);
	_strcat(errr, ": ");
	_strcat(errr, vtr);
	_strcat(errr, ": ");
	_strcat(errr, data_sh->args[0]);
	_strcat(errr, ": not found\n");
	_strcat(errr, "\0");
	free(vtr);

	return (errr);
}

/**
 * err_shell_exit - generates a generic error message for
 *                  "exit" command in get_exit.
 * @data_sh: data relevant to the shell (counter, arguments).
 *
 * Return: The error message.
 */
char *err_shell_exit(shll_comm *data_sh)
{
	char *errr, *vtr;
	int lgth;

	vtr = conv_itoa(data_sh->counter);
	lgth = _strlen(data_sh->argv[0]) + _strlen(vtr);
	lgth += _strlen(data_sh->args[0]) + _strlen(data_sh->args[1]) + 23;
	errr = malloc(sizeof(char) * (lgth + 1));
	if (errr == 0)
	{
		free(vtr);
		return (NULL);
	}
	_strcpy(errr, data_sh->argv[0]);
	_strcat(errr, ": ");
	_strcat(errr, vtr);
	_strcat(errr, ": ");
	_strcat(errr, data_sh->args[0]);
	_strcat(errr, ": Illegal number: ");
	_strcat(errr, data_sh->args[1]);
	_strcat(errr, "\n\0");
	free(vtr);

	return (errr);
}

/**
 * err_gcd - generates an error message for the 'cd' command in get_cd.
 * @data_sh: data relevant to the shell (directory).
 *
 * Return: The error message.
 */
char *err_gcd(shll_comm *data_sh)
{
	char *errr, *vtr, *ermg;
	int le, leid;

	vtr = conv_itoa(data_sh->counter);
	if (data_sh->args[1][0] == '-')
	{
		ermg = ": Illegal option ";
		leid = 2;
	}
	else
	{
		ermg = ": can't cd to ";
		leid = _strlen(data_sh->args[1]);
	}

	le = _strlen(data_sh->argv[0]) + _strlen(data_sh->args[0]);
	le += _strlen(vtr) + _strlen(ermg) + leid + 5;
	errr = malloc(sizeof(char) * (le + 1));

	if (errr == 0)
	{
		free(vtr);
		return (NULL);
	}

	errr = conc_err_msg(data_sh, ermg, errr, vtr);

	free(vtr);

	return (errr);
}
