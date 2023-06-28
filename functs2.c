#include "main.h"

/**
 * conv_itoa - Converts an integer to a string.
 * @number: The integer number to convert.
 *
 * Return: The string representation of the integer.
 */
char *conv_itoa(int number)
{
	unsigned int nn;
	int ln = get_length(number);
	char *buf;

	buf = malloc(sizeof(char) * (ln + 1));
	if (buf == 0)
		return (NULL);

	*(buf + ln) = '\0';

	if (number < 0)
	{
		nn = number * -1;
		buf[0] = '-';
	}
	else
		nn = number;

	ln--;
	do {
		*(buf + ln) = (nn % 10) + '0';
		nn = nn / 10;
		ln--;
	} while (nn > 0);
	return (buf);
}

/**
 * get_length - Get the length of a number.
 * @number: The number for which to calculate the length.
 *
 * Return: The length of the number.
 */
int get_length(int number)
{
	unsigned int nn;
	int lght = 1;

	if (number < 0)
	{
		lght++;
		nn = number * -1;
	}
	else
		nn = number;
	while (nn > 9)
	{
		lght++;
		nn = nn / 10;
	}

	return (lght);
}

/**
 * _atoi - Converts a string to an integer.
 * @str: Input string.
 *
 * Return: The converted integer.
 */
int _atoi(char *str)
{
	unsigned int counter = 0, siz = 0, o = 0, pnp = 1, mn = 1, j;

	while (*(str + counter) != '\0')
	{
		if (siz > 0 && (*(str + counter) < '0' || *(str + counter) > '9'))
			break;

		if (*(str + counter) == '-')
			pnp *= -1;

		if ((*(str + counter) >= '0') && (*(str + counter) <= '9'))
		{
			if (siz > 0)
				mn *= 10;
			siz++;
		}
		counter++;
	}

	for (j = counter - siz; j < counter; j++)
	{
		o = o + ((*(str + j) - 48) * mn);
		mn /= 10;
	}
	return (o * pnp);
}
