// Passed Moulinette 2019.09.01

// This code was heavily influenced by dfonarev's solution (github.com/ruv1nce)

#include <stdlib.h>
#include <string.h>

int		factorial(int n)
{
	int out = n;
	while (--n > 1)
		out *= n;
	return (out);
}

void	permute(int **tab, int *avail, int *soln_buf, int n, int soln_i, int *tab_i)
{
	if (soln_i == n)
	{
		//copy soln from buffer to output tab
		memcpy(tab[++(*tab_i)], soln_buf, sizeof(int) * n);
		// (*tab_i)++;
		// for (int j = 0; j < n; ++j)
		// 	tab[*tab_i][j] = soln_buf[j];
	}
	else
	{
		// Loop through values to put into soln_buf at current index
		int i = 0;
		while (i < n)
		{
			if (avail[i] == 1)
			{
				//copy current value into soln_buf, mark as unavailable and recur
				soln_buf[soln_i] = i;
				avail[i] = 0;	// Set i as unavailable to be used in recursion
				permute(tab, avail, soln_buf, n, soln_i + 1, tab_i);
				avail[i] = 1;	// Make sure to reset i as available!
			}
			++i;
		}
	}
}

int		**range_comb(int n)
{
	if (n <= 0)
		return (0);

	int i = -1;
	int soln_buf[n];
	int permutations = factorial(n);
	int avail[n];
	while (++i < n)
		avail[i] = 1;

	int **tab = malloc(sizeof(*tab) * (permutations + 1));
	tab[permutations] = 0;

	i = -1;
	while (++i < permutations)
		tab[i] = malloc(sizeof(**tab) * n);

	int tab_i = -1;
	permute(tab, avail, soln_buf, n, 0, &tab_i);
	return (tab);
}

#ifdef TEST		// To enable this block of code, compile with `-D TEST`
#include <stdio.h>
int	main(void)
{
	int n = 4;
	int **arr = range_comb(n);
	int i = -1;
	int j;
	int size = factorial(n);
	while (++i < size)
	{
		j = -1;
		while (++j < n)
			printf("%d, ", arr[i][j]);
		printf("\n");
	}
}
#endif