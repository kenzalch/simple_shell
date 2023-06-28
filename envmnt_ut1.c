#include "main.h"

/**
 * verify_env - Checks if the typed variable is an environment variable.
 * @hd: Head of the linked list.
 * @inp: Input string.
 * @shell_data: Data structure.
 *
 * Return: No return.
 */
void verify_env(r_var **hd, char *inp, shll_comm *shell_data)
{
	int li, chc, j, lft_vale;
	char **_envm;

	_envm = shell_data->_env;
	for (li = 0; _envm[li]; li++)
	{
		for (j = 1, chc = 0; _envm[li][chc]; chc++)
		{
			if (_envm[li][chc] == '=')
			{
				lft_vale = _strlen(_envm[li] + chc + 1);
				add_var_nd(hd, j, _envm[li] + chc + 1, lft_vale);
				return;
			}

			if (inp[j] == _envm[li][chc])
				j++;
			else
				break;
		}
	}

	for (j = 0; inp[j]; j++)
	{
		if (inp[j] == ' ' || inp[j] == '\t' || inp[j] == ';' || inp[j] == '\n')
			break;
	}

	add_var_nd(hd, j, NULL, 0);
}

/**
 * rpl_inp - Replaces variables in the input string.
 * @hd: Head of the linked list.
 * @inp: Input string.
 * @new_inp: New input string (replaced).
 * @numlen: New length.
 *
 * Return: Replaced string.
 */
char *rpl_inp(r_var **hd, char *inp, char *new_inp, int numlen)
{
	r_var *idx;
	int j, le, n;

	idx = *hd;
	for (le = j = 0; j < numlen; j++)
	{
		if (inp[le] == '$')
		{
			if (!(idx->len_var) && !(idx->len_val))
			{
				new_inp[j] = inp[le];
				le++;
			}
			else if (idx->len_var && !(idx->len_val))
			{
				for (n = 0; n < idx->len_var; n++)
					le++;
				j--;
			}
			else
			{
				for (n = 0; n < idx->len_val; n++)
				{
					new_inp[j] = idx->val[n];
					j++;
				}
				le += (idx->len_var);
				j--;
			}
			idx = idx->next;
		}
		else
		{
			new_inp[j] = inp[le];
			le++;
		}
	}

	return (new_inp);
}

/**
 * verify_vars - Check if the typed variable is $$ or $?
 * @header: Head of the linked list.
 * @inp: Input string.
 * @str: Last status of the shell.
 * @datashell: Data structure.
 *
 * Return: Number of characters processed.
 */
int verify_vars(r_var **header, char *inp, char *str, shll_comm *datashell)
{
	int j, lftst, lftpd;

	lftst = _strlen(str);
	lftpd = _strlen(datashell->pid);

	for (j = 0; inp[j]; j++)
	{
		if (inp[j] == '$')
		{
			if (inp[j + 1] == '?')
				add_var_nd(header, 2, str, lftst), j++;
			else if (inp[j + 1] == '$')
				add_var_nd(header, 2, datashell->pid, lftpd), j++;
			else if (inp[j + 1] == '\n')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[j + 1] == '\0')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[j + 1] == ' ')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[j + 1] == '\t')
				add_var_nd(header, 0, NULL, 0);
			else if (inp[j + 1] == ';')
				add_var_nd(header, 0, NULL, 0);
			else
				verify_env(header, inp + j, datashell);
		}
	}

	return (j);
}

/**
 * compare_envname - Compares the name of an environment
 *                   variable with a given name.
 * @name_env: Name of the environment variable.
 * @name_ptr: Name to compare against.
 *
 * Return: 0 if the names are not equal. A value
 *         greater than 0 if they are equal.
 */
int compare_envname(const char *name_env, const char *name_ptr)
{
	int idx;

	for (idx = 0; name_env[idx] != '='; idx++)
	{
		if (name_env[idx] != name_ptr[idx])
		{
			return (0);
		}
	}

	return (idx + 1);
}
