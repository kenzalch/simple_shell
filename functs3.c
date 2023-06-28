#include "main.h"

/**
 * _strspn - Calculates the length of the initial segment of a
 *           string that consists of only accepted bytes.
 * @str: Pointer to the string to search.
 * @acc: Pointer to the accepted bytes.
 *
 * Return: The length of the prefix substring that consists
 *         of only accepted bytes.
 */
int _strspn(char *str, char *acc)
{
	int k, l, bool;

	for (k = 0; *(str + k) != '\0'; k++)
	{
		bool = 1;
		for (l = 0; *(acc + l) != '\0'; l++)
		{
			if (*(str + k) == *(acc + l))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}

	return (k);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 *
 * Return: Pointer to the destination string after concatenation.
 */
char *_strcat(char *dest, const char *src)
{
	int k, l;

	for (k = 0; dest[k] != '\0'; k++)
		;

	for (l = 0; src[l] != '\0'; l++)
	{
		dest[k] = src[l];
		k++;
	}

	dest[k] = '\0';

	return (dest);
}

/**
 * _strcmp - Compares two strings.
 * @str1: Pointer to the first string to compare.
 * @str2: Pointer to the second string to compare.
 *
 * Return: 0 if the strings are equal, a positive value if str1 is greater,
 *         a negative value if str2 is greater.
 */
int _strcmp(char *str1, char *str2)
{
	int k;

	for (k = 0; str1[k] == str2[k] && str1[k]; k++)
		;

	if (str1[k] > str2[k])
		return (1);
	if (str1[k] < str2[k])
		return (-1);

	return (0);
}

/**
 * _strchr - Locates a character in a string.
 * @str: Pointer to the string to search.
 * @c: Character to locate.
 *
 * Return: Pointer to the first occurrence of the character 'c' in 'str',
 *         or NULL if the character is not found.
 */
char *_strchr(char *str, char c)
{
	unsigned int l = 0;

	for (; *(str + l) != '\0'; l++)
		if (*(str + l) == c)
			return (str + l);
	if (*(str + l) == c)
		return (str + l);
	return ('\0');
}

/**
 * _strcpy - Copies the string pointed to by src to dest.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{

	size_t b;

	for (b = 0; src[b] != '\0'; b++)
		dest[b] = src[b];

	dest[b] = '\0';

	return (dest);
}
