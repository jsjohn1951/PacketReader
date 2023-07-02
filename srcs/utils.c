/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:55:32 by wismith           #+#    #+#             */
/*   Updated: 2023/06/27 16:23:32 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/utils.h"

/** @brief returns the length of a string.
 * 	@note takes char * type as argument.
*/
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/** @brief Writes to a specific file descriptor.
 * @note takes in file descriptor, and char * as arguments.
 * @note returns how many characters have been written.
*/
size_t	ft_putstr(int fd, char *s)
{
	return (write(fd, s, ft_strlen(s)));
}

/** @brief allocates a new string and copies the string being
 * 			passed as arguments.
 * @note In case of malloc failing, return (NULL);
*/
char	*ft_strdup(char *s)
{
	char	*res;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	while (i < size)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/** @brief compares two strings */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/** @brief returns the comparison of argv[1]
 * 			extension and a diff string.
*/
int	cmpExt(char *arg, char *diff)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '.')
			return (ft_strcmp(arg + i, diff));
	return (-1);
}

/** @brief function to exit the program in case of
 * 			error.
 * @note prints error information to stderr
*/
void	err(char *err)
{
	ft_putstr(1, KRED);
	ft_putstr(2, err);
	ft_putstr(1, KNRM);
	ft_putstr(1, INFO);
	exit(-1);
}

/** @brief function to join two strings together */
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = -1;
	j = -1;
	if (s1)
		while (s1[++i])
			res[i] = s1[i];
	if (s2)
		while (s2[++j])
		{
			res[i] = s2[j];
			i++;
		}
	res[i] = '\0';
	return (res);
}

/** @brief function to reverse a string.
 * @note takes void * as argument.
 * 
*/
void	ft_strrev(void *s)
{
	char	tmp;
	char	*s1;
	char	*s2;

	s1 = (char *)s;
	s2 = (char *) s + ft_strlen((char *)s) - 1;
	while (s1 < s2)
	{
		tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
		s1++;
		s2--;
	}
}

/** @brief function to convert from 
 * 			u_int16_t to string.
*/
char	*num_str_gen( size_t n )
{
	char		res[21];
	int			i;

	i = 0;
	while ( n )
	{
		res[i] = (n % 10) + 48;
		n /= 10;
		i++;
	}
	res[i] = '\0';
	ft_strrev( res );
	return ( ft_strdup( res ) );
}

/** @brief function to free a variable number of allocated pointers */
void	*free_all(int num, ...)
{
	va_list	args;
	int		i = 0;

	va_start(args, num);
	while (i < num)
	{
		void	*arg = va_arg(args, void *);
		if (arg)
			free (arg);
		i++;
	}
	va_end(args);
	return (NULL);
}
