#include "main.h"
/**
 * exit_sh - Exits the shell
 * @datashell: Data structure containing relevant data
 *             (status and args)
 *
 * Return: 0 on success.
 */
int exit_sh(shll_comm *datashell)
{
	unsigned int ustt;
	int is_d, strl, bg_n;

	if (datashell->args[1] != NULL)
	{
		ustt = _atoi(datashell->args[1]);
		is_d = _isdigit(datashell->args[1]);
		strl = _strlen(datashell->args[1]);
		bg_n = ustt > (unsigned int)INT_MAX;
		if (!is_d || strl > 10 || bg_n)
		{
			get_err(datashell, 2);
			datashell->stat = 2;
			return (1);
		}
		datashell->stat = (ustt % 256);
	}
	return (0);
}

/**
 * execute_line - Finds built-ins and commands.
 * @datash: Data relevant (args).
 *
 * Return: 1 on success.
 */
int execute_line(shll_comm *datash)
{
	int (*builtin)(shll_comm *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_bltn(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (command_exec(datash));
}

/**
 * err_environ - generates an error message for env-related operations.
 * @data_sh: data relevant to the shell (counter, arguments).
 *
 * Return: Error message string.
 */
char *err_environ(shll_comm *data_sh)
{
	int lgth;
	char *er, *txto, *vtr;

	vtr = conv_itoa(data_sh->counter);
	txto = ": Unable to add/remove from environment\n";
	lgth = _strlen(data_sh->argv[0]) + _strlen(vtr);
	lgth += _strlen(data_sh->args[0]) + _strlen(txto) + 4;
	er = malloc(sizeof(char) * (lgth + 1));
	if (er == 0)
	{
		free(er);
		free(vtr);
		return (NULL);
	}

	_strcpy(er, data_sh->argv[0]);
	_strcat(er, ": ");
	_strcat(er, vtr);
	_strcat(er, ": ");
	_strcat(er, data_sh->args[0]);
	_strcat(er, txto);
	_strcat(er, "\0");
	free(vtr);

	return (er);
}

/**
 * err_path126 - generates an error message for path-related
 *                operations with permission denied.
 * @data_sh: data relevant to the shell (counter, arguments).
 *
 * Return: The error message string.
 */
char *err_path126(shll_comm *data_sh)
{
	int lgth;
	char *vtr, *er;

	vtr = conv_itoa(data_sh->counter);
	lgth = _strlen(data_sh->argv[0]) + _strlen(vtr);
	lgth += _strlen(data_sh->args[0]) + 24;
	er = malloc(sizeof(char) * (lgth + 1));
	if (er == 0)
	{
		free(er);
		free(vtr);
		return (NULL);
	}
	_strcpy(er, data_sh->argv[0]);
	_strcat(er, ": ");
	_strcat(er, vtr);
	_strcat(er, ": ");
	_strcat(er, data_sh->args[0]);
	_strcat(er, ": Permission denied\n");
	_strcat(er, "\0");
	free(vtr);
	return (er);
}

/**
 * conc_err_msg - concatenates an error message for the 'cd' command.
 * @data_sh: data relevant to the shell (directory, arguments).
 * @disp_msg: message to be displayed.
 * @err: output message buffer.
 * @vstr: counter lines.
 *
 * Return: The concatenated error message.
 */
char *conc_err_msg(shll_comm *data_sh, char *disp_msg, char *err, char *vstr)
{
	char *ill_flg;

	_strcpy(err, data_sh->argv[0]);
	_strcat(err, ": ");
	_strcat(err, vstr);
	_strcat(err, ": ");
	_strcat(err, data_sh->args[0]);
	_strcat(err, disp_msg);
	if (data_sh->args[1][0] == '-')
	{
		ill_flg = malloc(3);
		ill_flg[0] = '-';
		ill_flg[1] = data_sh->args[1][1];
		ill_flg[2] = '\0';
		_strcat(err, ill_flg);
		free(ill_flg);
	}
	else
	{
		_strcat(err, data_sh->args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}
