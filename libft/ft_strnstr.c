/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:15:45 by rsoo              #+#    #+#             */
/*   Updated: 2023/05/29 08:53:32 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystk, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return ((char *)haystk);
	if (n == 0)
		return (0);
	while (haystk[i] && i < n)
	{
		j = 0;
		while (needle[j] && needle[j] == haystk[i + j] && i + j < n)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystk[i]);
		i++;
	}
	return (0);
}

// Notes:
// (char*)haystk = the cast is to deal with const (returning 
// it is techinically making changes to it) so it tells to 
// compiler to ignore it by casting it to char*

// #include <stdio.h>
// int main()
// {
//     int i;
//     char haystk[] = "ababac";
//     char needle[] = "abac";
//     char *ptr = ft_strnstr(haystk, needle, 15);

//     while (ptr[i])
//         printf("%c", ptr[i++]);
//     printf("\n");
//     printf("Position of needle: %d\n", (int)(ptr - haystk));
// }
