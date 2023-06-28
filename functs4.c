#include "main.h"

/**
 * _strlen - Returns the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(const char *str)
{
	int lgh;

	for (lgh = 0; str[lgh] != 0; lgh++)
	{
	}
	return (lgh);
}

/**
 * _isdigit - Determines if a string consists only of numeric digits.
 * @str: The input string to be checked.
 *
 * Return: 1 if the string consists only of numeric digits, 0 otherwise.
 */
int _isdigit(const char *str)
{
	unsigned int j;

	for (j = 0; str[j]; j++)
		if (str[j] < 48 || str[j] > 57)
			return (0);
	return (1);
}

/**
 * _strdup - Duplicates a string in the heap memory.
 * @str: Type char pointer representing the string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	char *newe;
	size_t lgth;

	lgth = _strlen(str);
	newe = malloc(sizeof(char) * (lgth + 1));
	if (newe == NULL)
		return (NULL);
	_memcpy(newe, str, lgth + 1);

	return (newe);
}

/**
 * compare_chars - Compares characters of strings.
 * @str: Input string to compare.
 * @delimiter: Delimiter string for comparison.
 *
 * Return: 1 if the characters are equal, 0 otherwise.
 */
int compare_chars(char str[], const char *delimiter)
{
	unsigned int j, k, n;

	for (j = 0, n = 0; str[j]; j++)
	{
		for (k = 0; delimiter[k]; k++)
		{
			if (str[j] == delimiter[k])
			{
				n++;
				break;
			}
		}
	}
	if (j == n)
		return (1);
	return (0);
}

/**
 * _strtok - Splits a string by a specified delimiter.
 * @str: Input string to be split.
 * @delimiter: Delimiter string.
 *
 * Return: Pointer to the next token in the string,
 *         or NULL if no more tokens are found.
 */
char *_strtok(char str[], const char *delimiter)
{
	static char *spled, *st_end;
	char *st_start;
	unsigned int j, bool;

	if (str != NULL)
	{
		if (compare_chars(str, delimiter))
			return (NULL);
		spled = str; /*Store first address*/
		j = _strlen(str);
		st_end = &str[j]; /*Store last address*/
	}
	st_start = spled;
	if (st_start == st_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *spled; spled++)
	{
		/*Breaking loop finding the next token*/
		if (spled != st_start)
			if (*spled && *(spled - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (j = 0; delimiter[j]; j++)
		{
			if (*spled == delimiter[j])
			{
				*spled = '\0';
				if (spled == st_start)
					st_start++;
				break;
			}
		}
		if (bool == 0 && *spled) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (st_start);
}
