#include "main.h"
/**
 * add_ln_nd_end - Adds a command line at the end of a line_list.
 * @hd: Head of the linked list.
 * @cmd_line: Command line.
 *
 * Return: Address of the head.
 */
line_list *add_ln_nd_end(line_list **hd, char *cmd_line)
{
	line_list *nwe, *tp;

	nwe = malloc(sizeof(line_list));
	if (nwe == NULL)
		return (NULL);

	nwe->line = cmd_line;
	nwe->next = NULL;
	tp = *hd;

	if (tp == NULL)
	{
		*hd = nwe;
	}
	else
	{
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = nwe;
	}

	return (*hd);
}

/**
 * free_line_ls - Frees a line_list.
 * @hd: Head of the linked list.
 *
 * Return: No return.
 */
void free_line_ls(line_list **hd)
{
	line_list *tp;
	line_list *cur;

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

/**
 * add_node_en - Adds a separator found at the end
 * of a sep_list.
 * @hd: Head of the linked list.
 * @sp: Separator found (; | &).
 *
 * Return: Address of the head.
 */
sep_list *add_node_en(sep_list **hd, char sp)
{
	sep_list *newe_n, *tp;

	newe_n = malloc(sizeof(sep_list));
	if (newe_n == NULL)
		return (NULL);

	newe_n->sep = sp;
	newe_n->next = NULL;
	tp = *hd;

	if (tp == NULL)
	{
		*hd = newe_n;
	}
	else
	{
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = newe_n;
	}

	return (*hd);
}

/**
 * free_sp_ls - Frees a sep_list.
 * @hd: Head of the linked list.
 *
 * Return: No return.
 */
void free_sp_ls(sep_list **hd)
{
	sep_list *tp;
	sep_list *cur;

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
