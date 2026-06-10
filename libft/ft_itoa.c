#include "libft.h"

static int	digits_count(int n);

/**
 * @brief Convert an integer to a string.
 * @param n Integer to convert.
 * @return string, or NULL if allocation fails.
 */
char	*ft_itoa(int n)
{
	int		neg;
	int		dcount;
	char	*res;

	neg = 0;
	if (n < 0)
		neg = 1;
	dcount = digits_count(n) + neg;
	res = (char *)malloc(sizeof(char) * (dcount + 1));
	if (!res)
		return (NULL);
	res[dcount] = '\0';
	if (neg)
	{
		*res = '-';
		res[--dcount] = -(n % 10) + '0';
		n = -(n / 10);
	}
	while (dcount-- - neg)
	{
		res[dcount] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}

static int	digits_count(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		digits = 1;
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}
