#include "main.h"

/**
 * _whch - Locates a command.
 * @command: Command name.
 * @_env: Environment variable.
 *
 * Return: Location of the command.
 */
char *_whch(char *command, char **_env)
{
	char *way_name, *ptrway, *tkn_way, *dir;
	int lgth_dir, lgth_cmd, idx;
	struct stat st;

	way_name = get_environ("PATH", _env);
	if (way_name)
	{
		ptrway = _strdup(way_name);
		lgth_cmd = _strlen(command);
		tkn_way = _strtok(ptrway, ":");
		idx = 0;
		while (tkn_way != NULL)
		{
			if (check_cdir(way_name, &idx))
				if (stat(command, &st) == 0)
					return (command);
			lgth_dir = _strlen(tkn_way);
			dir = malloc(lgth_dir + lgth_cmd + 2);
			_strcpy(dir, tkn_way);
			_strcat(dir, "/");
			_strcat(dir, command);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptrway);
				return (dir);
			}
			free(dir);
			tkn_way = _strtok(NULL, ":");
		}
		free(ptrway);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * check_cdir - Checks if ":" is present in the current directory.
 * @filepath: Pointer to a character string representing the filepath.
 * @index: Pointer to an integer representing the index.
 *
 * Return: 1 if the path is searchable in the current directory, 0 otherwise.
 */
int check_cdir(char *filepath, int *index)
{
	if (filepath[*index] == ':')
		return (1);

	while (filepath[*index] != ':' && filepath[*index])
	{
		*index += 1;
	}

	if (filepath[*index])
		*index += 1;

	return (0);
}

/**
 * check_error_command - Verifies if the user has permissions
 *                      to access a command or directory.
 * @dir_dest: Destination directory.
 * @datashell: Data structure.
 *
 * Return: 1 if there is an error, 0 if not.
 */
int check_error_command(char *dir_dest, shll_comm *datashell)
{
	if (dir_dest == NULL)
	{
		get_err(datashell, 127);
		return (1);
	}

	if (_strcmp(datashell->args[0], dir_dest) != 0)
	{
		if (access(dir_dest, X_OK) == -1)
		{
			get_err(datashell, 126);
			free(dir_dest);
			return (1);
		}
		free(dir_dest);
	}
	else
	{
		if (access(datashell->args[0], X_OK) == -1)
		{
			get_err(datashell, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * command_exec - Executes command lines.
 * @datashell: Data relevant (args and input).
 *
 * Return: 1 on success.
 */
int command_exec(shll_comm *datashell)
{
	pid_t pim, wpid;
	int ste, exc;
	char *dyr;
	(void)wpid;

	exc = is_exec(datashell);
	if (exc == -1)
		return (1);
	if (exc == 0)
	{
		dyr = _whch(datashell->args[0], datashell->_env);
		if (check_error_command(dyr, datashell) == 1)
			return (1);
	}

	pim = fork();
	if (pim == 0)
	{
		if (exc == 0)
			dyr = _whch(datashell->args[0], datashell->_env);
		else
			dyr = datashell->args[0];
		execve(dyr + exc, datashell->args, datashell->_env);
	}
	else if (pim < 0)
	{
		perror(datashell->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpid = waitpid(pim, &ste, WUNTRACED);
		} while (!WIFEXITED(ste) && !WIFSIGNALED(ste));
	}

	datashell->stat = ste / 256;

	return (1);
}

/**
 * is_exec - Determines if a command is an executable.
 * @datashell: Data structure.
 *
 * Return: 0 if it's not an executable, otherwise a positive number.
 */
int is_exec(shll_comm *datashell)
{
	struct stat status;
	int idx;
	char *ip;

	ip = datashell->args[0];
	for (idx = 0; ip[idx]; idx++)
	{
		if (ip[idx] == '.')
		{
			if (ip[idx + 1] == '.')
				return (0);
			if (ip[idx + 1] == '/')
				continue;
			else
				break;
		}
		else if (ip[idx] == '/' && idx != 0)
		{
			if (ip[idx + 1] == '.')
				continue;
			idx++;
			break;
		}
		else
			break;
	}
	if (idx == 0)
		return (0);

	if (stat(ip + idx, &status) == 0)
		return (idx);
	get_err(datashell, 127);

	return (-1);
}
