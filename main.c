#include "main.h"
/**
 * main - Entry point.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	shll_comm dtsh;
	(void)argc;

	signal(SIGINT, get_sigint);
	set_datashell(&dtsh, argv);
	looping_shll(&dtsh);
	empty_data(&dtsh);
	if (dtsh.stat < 0)
		return (255);
	return (dtsh.stat);
}
