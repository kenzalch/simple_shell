#include "main.h"

/**
 * move_nxt - Moves to the next command line stored.
 * @lis_s: Separator list.
 * @lis_l: Command line list.
 * @data_shell: Data structure.
 *
 * Return: No return value.
 */
void move_nxt(sep_list **lis_s, line_list **lis_l, shll_comm *data_shell)
{
	int lp_sep;
	sep_list *ls_se;
	line_list *ls_le;

	lp_sep = 1;
	ls_se = *lis_s;
	ls_le = *lis_l;

	while (ls_se != NULL && lp_sep)
	{
		if (data_shell->stat == 0)
		{
			if (ls_se->sep == '&' || ls_se->sep == ';')
				lp_sep = 0;
			if (ls_se->sep == '|')
				ls_le = ls_le->next, ls_se = ls_se->next;
		}
		else
		{
			if (ls_se->sep == '|' || ls_se->sep == ';')
				lp_sep = 0;
			if (ls_se->sep == '&')
				ls_le = ls_le->next, ls_se = ls_se->next;
		}
		if (ls_se != NULL && !lp_sep)
			ls_se = ls_se->next;
	}
	*lis_s = ls_se;
	*lis_l = ls_le;
}

/**
 * swp_character - Swaps '|' and '&' for non-printed characters
 *                 in a string.
 * @inp: Input string.
 * @boolean: Type of swap. If boolean is 0, swaps '|' and '&'
 *           for non-printed characters.
 *
 * Return: Swapped string.
 */
char *swp_character(char *inp, int boolean)
{
	int j;

	if (boolean == 0)
	{
		for (j = 0; inp[j]; j++)
		{
			if (inp[j] == '|')
			{
				if (inp[j + 1] != '|')
					inp[j] = 16;
				else
					j++;
			}

			if (inp[j] == '&')
			{
				if (inp[j + 1] != '&')
					inp[j] = 12;
				else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; inp[j]; j++)
		{
			inp[j] = (inp[j] == 16 ? '|' : inp[j]);
			inp[j] = (inp[j] == 12 ? '&' : inp[j]);
		}
	}
	return (inp);
}

/**
 * add_nd - Adds separators and command lines to the lists.
 * @hd_s: Head of the separator list.
 * @hd_l: Head of the command lines list.
 * @inp: Input string.
 *
 * Return: No return value.
 */
void add_nd(sep_list **hd_s, line_list **hd_l, char *inp)
{
	int j;
	char *cmd_line;

	inp = swp_character(inp, 0);

	for (j = 0; inp[j]; j++)
	{
		if (inp[j] == ';')
			add_node_en(hd_s, inp[j]);

		if (inp[j] == '|' || inp[j] == '&')
		{
			add_node_en(hd_s, inp[j]);
			j++;
		}
	}

	cmd_line = _strtok(inp, ";|&");
	do {
		cmd_line = swp_character(cmd_line, 1);
		add_ln_nd_end(hd_l, cmd_line);
		cmd_line = _strtok(NULL, ";|&");
	} while (cmd_line != NULL);
}

/**
 * read_line - Reads the input string.
 * @int_eof: Return value of the getline function.
 *
 * Return: Input string.
 */
char *read_line(int *int_eof)
{
	char *ip = NULL;
	size_t bufsize = 0;

	*int_eof = getline(&ip, &bufsize, stdin);

	return (ip);
}

/**
 * free_value_ls - Frees a r_var list.
 * @hd: Head of the linked list.
 * Return: No return.
 */
void free_value_ls(r_var **hd)
{
	r_var *tp;
	r_var *cur;

	if (hd != NULL)
	{
		cur = *hd;
		while ((tp = cur) != NULL)
		{
			cur = cur->next;
			free(tp);
		}
		*hd = NULL;
	}
}
