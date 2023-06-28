#include "main.h"

/**
 * changedir_shell - Changes the current directory.
 * @data_sh: Pointer to the data
 *
 * Return: 1 on success.
 */
int changedir_shell(shll_comm *data_sh)
{
	int inhm, inhm2, isdshboard;
	char *dir = data_sh->args[1];

	if (dir != NULL)
	{
		inhm = _strcmp("$HOME", dir);
		inhm2 = _strcmp("~", dir);
		isdshboard = _strcmp("--", dir);
	}

	if (dir == NULL || !inhm || !inhm2 || !isdshboard)
	{
		changedir_to_home(data_sh);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		changedir_prev(data_sh);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		chandir_dor(data_sh);
		return (1);
	}

	cd_to_dist(data_sh);

	return (1);
}

/**
 * chandir_dor - Changes to the parent directory.
 * @data_sh: Pointer to the data structure containing the
 *           environment variables.
 *
 * Return: No return value.
 */
void chandir_dor(shll_comm *data_sh)
{
	char pwd[PATH_MAX];
	char *dir, *c_prtwd, *c_stok_pwd;

	getcwd(pwd, sizeof(pwd));
	c_prtwd = _strdup(pwd);
	set_env("OLDPWD", c_prtwd, data_sh);
	dir = data_sh->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", c_prtwd, data_sh);
		free(c_prtwd);
		return;
	}
	if (_strcmp("/", c_prtwd) == 0)
	{
		free(c_prtwd);
		return;
	}
	c_stok_pwd = c_prtwd;
	rev_string(c_stok_pwd);
	c_stok_pwd = _stok(c_stok_pwd, "/");
	if (c_stok_pwd != NULL)
	{
		c_stok_pwd = _strtok(NULL, "\0");

		if (c_stok_pwd != NULL)
			rev_string(c_stok_pwd);
	}
	if (c_stok_pwd != NULL)
	{
		chdir(c_stok_pwd);
		set_env("PWD", c_stok_pwd, data_sh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data_sh);
	}
	data_sh->stat = 0;
	free(c_prtwd);
}

/**
 * cd_to_dist - Changes to a directory specified by the user.
 * @data_sh: Pointer to the data structure containing
 *           the directories.
 *
 * Return: No return value.
 */
void cd_to_dist(shll_comm *data_sh)
{
	char prtwd[PATH_MAX];
	char *dir, *c_pwd, *c_dir;

	getcwd(prtwd, sizeof(prtwd));

	dir = data_sh->args[1];
	if (chdir(dire) == -1)
	{
		get_err(data_sh, 2);
		return;
	}

	c_pwd = _strdup(prtwd);
	set_env("OLDPWD", c_pwd, data_sh);

	c_dir = _strdup(dir);
	set_env("PWD", c_dir, data_sh);

	free(c_pwd);
	free(c_dir);

	data_sh->stat = 0;

	chdir(dir);
}

/**
 * changedir_prev - Changes to the previous directory.
 * @data_sh: Data relevant to the environment and
 *           directories.
 *
 * Return: No return value.
 */
void changedir_prev(shll_comm *data_sh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_opwd, *c_pwd, *c_opwd;

	getcwd(pwd, sizeof(pwd));
	c_pwd = _strdup(pwd);

	p_opwd = get_environ("OLDPWD", data_sh->_env);

	if (p_opwd == NULL)
		c_opwd = c_pwd;
	else
		c_opwd = _strdup(p_opwd);

	set_env("OLDPWD", c_pwd, data_sh);

	if (chdir(c_opwd) == -1)
		set_env("PWD", c_pwd, data_sh);
	else
		set_env("PWD", c_opwd, data_sh);

	p_pwd = get_environ("PWD", data_sh->_env);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(c_pwd);
	if (p_opwd)
		free(c_opwd);

	data_sh->stat = 0;

	chdir(p_pwd);
}

/**
 * changedir_to_home - Changes to the home directory.
 * @data_sh: Data relevant to the environment.
 *
 * Return: No return value.
 */
void changedir_to_home(shll_comm *data_sh)
{
	char *prt_pwd, *hme;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	prt_pwd = _strdup(pwd);

	hme = get_environ("HOME", data_sh->_env);

	if (hme == NULL)
	{
		set_env("OLDPWD", prt_pwd, data_sh);
		free(prt_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_err(data_sh, 2);
		free(prt_pwd);
		return;
	}

	set_env("OLDPWD", prt_pwd, data_sh);
	set_env("PWD", hme, data_sh);
	free(prt_pwd);
	data_sh->stat = 0;
}
