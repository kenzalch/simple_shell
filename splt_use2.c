#include "main.h"
/**
 * splt_ln - Tokenizes the input string.
 * @inp: Input string.
 *
 * Return: String splitted.
 */
char **splt_ln(char *inp)
{
	size_t bsize;
	size_t j;
	char **toks;
	char *tok;

	bsize = TOK_BUFSIZE;
	toks = malloc(sizeof(char *) * (bsize));
	if (toks == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tok = _strtok(inp, TOK_DELIM);
	toks[0] = tok;

	for (j = 1; tok != NULL; j++)
	{
		if (j == bsize)
		{
			bsize += TOK_BUFSIZE;
			toks = _reallocdp(toks, j, sizeof(char *) * bsize);
			if (toks == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tok = _strtok(NULL, TOK_DELIM);
		toks[j] = tok;
	}

	return (toks);
}

/**
 * split_cmds - Splits command lines according to the separators ;, |, and &,
 *	      and executes them.
 * @datashell: Data structure.
 * @inp: Input string.
 *
 * Return: 0 to exit, 1 to continue.
 */
int split_cmds(shll_comm *datashell, char *inp)
{

	sep_list *hd_se, *ls_se;
	line_list *head_le, *list_le;
	int lping;

	hd_se = NULL;
	head_le = NULL;

	add_nd(&hd_se, &head_le, inp);

	ls_se = hd_se;
	list_le = head_le;

	while (list_le != NULL)
	{
		datashell->input = list_le->line;
		datashell->args = splt_ln(datashell->input);
		lping = execute_line(datashell);
		free(datashell->args);

		if (lping == 0)
			break;

		move_nxt(&ls_se, &list_le, datashell);

		if (list_le != NULL)
			list_le = list_le->next;
	}

	free_sp_ls(&hd_se);
	free_line_ls(&head_le);

	if (lping == 0)
		return (0);
	return (1);
}

/**
 * without_cmt - Deletes comments from the input.
 *
 * @input: Input string.
 * Return: Input without comments.
 */
char *without_cmt(char *input)
{
	int j, upe_to;

	upe_to = 0;
	for (j = 0; input[j]; j++)
	{
		if (input[j] == '#')
		{
			if (j == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[j - 1] == ' ' || input[j - 1] == '\t' || input[j - 1] == ';')
				upe_to = j;
		}
	}

	if (upe_to != 0)
	{
		input = _realloc(input, j, upe_to + 1);
		input[upe_to] = '\0';
	}

	return (input);
}

/**
 * looping_shll - Main loop of the shell
 * @data_shell: Data relevant to the shell (av, input, args)
 *
 * Return: No return.
 */
void looping_shll(shll_comm *data_shell)
{
	int lping, int_eof;
	char *ip;

	lping = 1;
	while (lping == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		ip = read_line(&int_eof);
		if (int_eof != -1)
		{
			ip = without_cmt(ip);
			if (ip == NULL)
				continue;

			if (ch_syn_err(data_shell, ip) == 1)
			{
				data_shell->stat = 2;
				free(ip);
				continue;
			}
			ip = replace_str(ip, data_shell);
			lping = split_cmds(data_shell, ip);
			data_shell->counter += 1;
			free(ip);
		}
		else
		{
			lping = 0;
			free(ip);
		}
	}
}

/**
 * add_var_nd - Adds a variable at the end of a r_var list.
 * @hd: Head of the linked list.
 * @lenvar: Length of the variable.
 * @value: Value of the variable.
 * @lenval: Length of the value.
 *
 * Return: Address of the head.
 */
r_var *add_var_nd(r_var **hd, int lenvar, char *value, int lenval)
{
	r_var *newend, *tmpe;

	newend = malloc(sizeof(r_var));
	if (newend == NULL)
		return (NULL);

	newend->len_var = lenvar;
	newend->val = value;
	newend->len_val = lenval;

	newend->next = NULL;
	tmpe = *hd;

	if (tmpe == NULL)
	{
		*hd = newend;
	}
	else
	{
		while (tmpe->next != NULL)
			tmpe = tmpe->next;
		tmpe->next = newend;
	}

	return (*hd);
}
