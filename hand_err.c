#include "main.h"

/**
 * first_character - finds the index of the first non-whitespace character.
 * @inp: intptr_t string.
 * @index: pointer to the index variable.
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int first_character(char *inp, int *index)
{

	for (*index = 0; inp[*index]; *index += 1)
	{
		if (inp[*index] == ' ' || inp[*index] == '\t')
			continue;

		if (inp[*index] == ';' || inp[*index] == '|' || inp[*index] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * disp_syn_err - displays a syntax error message.
 * @data_sh: data structure.
 * @inp: intptr_t string.
 * @index: index of the error.
 * @boolean: flag to control the error message.
 *
 * Return: No return value.
 */
void disp_syn_err(shll_comm *data_sh, char *inp, int index, int boolean)
{
	char *mg, *mg2, *mg3, *err, *comt;
	int lgth;

	if (inp[index] == ';')
	{
		if (boolean == 0)
			mg = (inp[index + 1] == ';' ? ";;" : ";");
		else
			mg = (inp[index - 1] == ';' ? ";;" : ";");
	}

	if (inp[index] == '|')
		mg = (inp[index + 1] == '|' ? "||" : "|");

	if (inp[index] == '&')
		mg = (inp[index + 1] == '&' ? "&&" : "&");

	mg2 = ": Syntax error: \"";
	mg3 = "\" unexpected\n";
	comt = conv_itoa(data_sh->comt);
	lgth = _strlen(data_sh->argv[0]) + _strlen(counter);
	lgth += _strlen(mg) + _strlen(mg2) + _strlen(mg3) + 2;

	err = malloc(sizeof(char) * (lgth + 1));
	if (err == 0)
	{
		free(comt);
		return;
	}
	_strcpy(err, data_sh->argv[0]);
	_strcat(err, ": ");
	_strcat(err, comt);
	_strcat(err, mg2);
	_strcat(err, mg);
	_strcat(err, mg3);
	_strcat(err, "\0");

	write(STDERR_FILENO, err, lgth);
	free(err);
	free(comt);
}

/**
 * ch_syn_err - intermediate function to find and print a syntax error.
 * @data_sh: data structure.
 * @inptrt: intptr_t string.
 *
 * Return: 1 if there is an error, 0 otherwise.
 */
int ch_syn_err(shll_comm *data_sh, char *inptrt)
{
	int frst = 0, fchc = 0, idx = 0;

	fchc = first_character(inptrt, &frst);
	if (fchc == -1)
	{
		disp_syn_err(data_sh, inptrt, frst, 0);
		return (1);
	}

	idx = sep_oper_error(inptrt + frst, 0, *(inptrt + frst));
	if (idx != 0)
	{
		disp_syn_err(data_sh, inptrt, frst + idx, 1);
		return (1);
	}

	return (0);
}

/**
 * dupl_chars - counts the repetitions of a character in a string.
 * @inp: intptr_t string.
 * @index: index.
 *
 * Return: The number of repetitions.
 */
int dupl_chars(char *inp, int index)
{
	if (*(inp - 1) == *inp)
		return (dupl_chars(inp - 1, index + 1));

	return (index);
}

/**
 * sep_oper_error - finds syntax errors in the intptr_t string.
 * @inp: intptr_t string.
 * @index: index.
 * @lastchar: last character read.
 *
 * Return: The index of the error. Returns 0 when there are no errors.
 */
int sep_oper_error(char *inp, int index, char lastchar)
{
	int comt = 0;

	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (sep_oper_error(inp + 1, index + 1, lastchar));

	if (*inp == ';')
		if (lastchar == '|' || lastchar == '&' || lastchar == ';')
			return (index);

	if (*inp == '|')
	{
		if (lastchar == ';' || lastchar == '&')
			return (index);

		if (lastchar == '|')
		{
			comt = dupl_chars(inp, 0);
			if (comt == 0 || comt > 1)
				return (index);
		}
	}

	if (*inp == '&')
	{
		if (lastchar == ';' || lastchar == '|')
			return (index);

		if (lastchar == '&')
		{
			comt = dupl_chars(inp, 0);
			if (comt == 0 || comt > 1)
				return (index);
		}
	}

	return (sep_oper_error(inp + 1, index + 1, *inp));
}
