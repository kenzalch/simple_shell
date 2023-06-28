#include "main.h"
/**
 * disp_help_general - Entry point for help information for the help builtin
 *
 * Return: Void
 */
void disp_help_general(void)
{
	char *hl = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = "unsetenv [variable]\n";
	write(STDOUT_FILENO, hl, _strlen(hl));
}
/**
 * disp_help_exit - Help information fot the builint exit
 *
 * Return: Void
 */
void disp_help_exit(void)
{
	char *hl = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, hl, _strlen(hl));
}

/**
 * display_unsetenv - Help information for the builtin unsetenv
 *
 * Return: Void
 */
void display_unsetenv(void)
{
	char *hl = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, hl, _strlen(hl));
	hl = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, hl, _strlen(hl));
}

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * get_ln - assigns the line var for get_line
 * @lnptr: Pointer to the line variable
 * @num: Pointer to the size of line variable
 * @buf: String that is being assigned to line
 * @size_b: Size of the buffer
 *
 * Return: void
 */
void get_ln(char **lnptr, size_t *num, char *buf, size_t size_b)
{

	if (*lnptr == NULL)
	{
		if (size_b > BUFSIZE)
			*num = size_b;

		else
			*num = BUFSIZE;
		*lnptr = buf;
	}
	else if (*num < size_b)
	{
		if (size_b > BUFSIZE)
			*num = size_b;
		else
			*num = BUFSIZE;
		*lnptr = buf;
	}
	else
	{
		_strcpy(*lnptr, buf);
		free(buf);
	}
}
