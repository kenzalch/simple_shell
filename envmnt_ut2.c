#include "main.h"

/**
 * replace_str - Calls functions to replace string into vars.
 * @inp: Input string.
 * @data_shell: Data structure.
 *
 * Return: Replaced string.
 */
char *replace_str(char *inp, shll_comm *data_shell)
{
	int oln, nln;
	r_var *hde, *idx;
	char *stt, *n_inp;

	stt = conv_itoa(data_shell->stat);
	hde = NULL;

	oln = verify_vars(&hde, inp, stt, data_shell);

	if (hde == NULL)
	{
		free(stt);
		return (inp);
	}

	idx = hde;
	nln = 0;

	while (idx != NULL)
	{
		nln += (idx->len_val - idx->len_var);
		idx = idx->next;
	}

	nln += oln;

	n_inp = malloc(sizeof(char) * (nln + 1));
	n_inp[nln] = '\0';

	n_inp = rpl_inp(&hde, inp, n_inp, nln);

	free(inp);
	free(stt);
	free_value_ls(&hde);

	return (n_inp);
}

/**
 * _unsetenv - Deletes an environment variable with the specified name.
 * @datash: Data structure containing the environment variable name.
 *
 * Return: 1 on success.
 */
int _unsetenv(shll_comm *datash)
{
	int m, n, o;
	char **rl_env;
	char *vrenv, *nmenv;

	if (datash->args[1] == NULL)
	{
		get_err(datash, -1);
		return (1);
	}
	o = -1;
	for (m = 0; datash->_env[m]; m++)
	{
		vrenv = _strdup(datash->_env[m]);
		nmenv = _strtok(vrenv, "=");
		if (_strcmp(nmenv, datash->args[1]) == 0)
		{
			o = m;
		}
		free(vrenv);
	}
	if (o == -1)
	{
		get_err(datash, -1);
		return (1);
	}
	rl_env = malloc(sizeof(char *) * (m));
	for (m = n = 0; datash->_env[m]; m++)
	{
		if (m != o)
		{
			rl_env[n] = datash->_env[m];
			n++;
		}
	}
	rl_env[n] = NULL;
	free(datash->_env[o]);
	free(datash->_env);
	datash->_env = rl_env;
	return (1);
}

/**
 * set_env - Sets an environment variable.
 * @environ_name: Name of the environment variable.
 * @val: Value of the environment variable.
 * @data_sh: Data structure containing the environment variables.
 *
 * Return: No return.
 */
void set_env(char *environ_name, char *val, shll_comm *data_sh)
{
	int n;
	char *vrenv, *nmenv;

	for (n = 0; data_sh->_env[n]; n++)
	{
		vrenv = _strdup(data_sh->_env[n]);
		nmenv = _strtok(vrenv, "=");
		if (_strcmp(nmenv, environ_name) == 0)
		{
			free(data_sh->_env[n]);
			data_sh->_env[n] = cp_info(nmenv, val);
			free(vrenv);
			return;
		}
		free(vrenv);
	}

	data_sh->_env = _reallocdp(data_sh->_env, n, sizeof(char *) * (n + 2));
	data_sh->_env[n] = cp_info(environ_name, val);
	data_sh->_env[n + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 *           with the name passed.
 * @data_sh: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(shll_comm *data_sh)
{

	if (data_sh->args[1] == NULL || data_sh->args[2] == NULL)
	{
		get_err(data_sh, -1);
		return (1);
	}

	set_env(data_sh->args[1], data_sh->args[2], data_sh);

	return (1);
}

/**
 * cp_info - Copies information to create a new environment variable or alias.
 * @alias_name: Name of the environment variable or alias.
 * @val: Value of the environment variable or alias.
 *
 * Return: New environment variable or alias.
 */
char *cp_info(char *alias_name, char *val)
{
	char *nw;
	int l_name, l_value, l;

	l_name = _strlen(alias_name);
	l_value = _strlen(val);
	l = l_name + l_value + 2;
	nw = malloc(sizeof(char) * (l));
	_strcpy(nw, alias_name);
	_strcat(nw, "=");
	_strcat(nw, val);
	_strcat(nw, "\0");

	return (nw);
}
