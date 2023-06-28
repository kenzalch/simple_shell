#include "main.h"

/**
 * disp_help_cd - Help information for the builtin alias.
 *
 * Return: no return
 */
void disp_help_cd(void)
{
	char *hp = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, hp, _strlen(hp));
	hp = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, hp, _strlen(hp));
}

/**
 * disp_help_alias - Help information for the builtin alias.
 *
 * Return: no return
 */
void disp_help_alias(void)
{
	char *hp = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, hp, _strlen(hp));
	hp = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, hp, _strlen(hp));
}

/**
 * disp_help - Help information for the builtin help.
 *
 * Return: no return
 */
void disp_help(void)
{
	char *hp = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, hp, _strlen(hp));
	hp = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, hp, _strlen(hp));
	hp = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, hp, _strlen(hp));
}

/**
 * disp_help_env - Help information for the builtin env
 *
 * Return: no return
 */
void disp_help_env(void)
{
	char *hp = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, hp, _strlen(hp));
	hp = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, hp, _strlen(hp));
}

/**
 * disp_help_setenv - Help information for the builtin setenv
 *
 * Return: no return
 */
void disp_help_setenv(void)
{

	char *assist = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "int replace)\n\t";
	write(STDOUT_FILENO, assist, _strlen(assist));
	assist = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, assist, _strlen(assist));
}
