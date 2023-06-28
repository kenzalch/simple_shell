#include "main.h"
/**
 * rev_string - Reverses the characters in a given string.
 * @s: The input string to be reversed.
 *
 * Return: Void
 */
void rev_string(char *s)
{
	int comt = 0, k, l;
	char *stre, tempe;

	while (comt >= 0)
	{
		if (s[comt] == '\0')
			break;
		comt++;
	}
	stre = s;

	for (k = 0; k < (comt - 1); k++)
	{
		for (l = k + 1; l > 0; l--)
		{
			tempe = *(stre + l);
			*(stre + l) = *(stre + (l - 1));
			*(stre + (l - 1)) = tempe;
		}
	}
}
