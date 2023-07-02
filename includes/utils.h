/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:42:49 by wismith           #+#    #+#             */
/*   Updated: 2023/06/27 16:23:48 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

# define ERRNUMARGS	"Incorrect number of arguments!\n\n"
# define ERRARGEXT	"Incorrect file extension for pcap!\n\n"
# define ERRPCAP	"Unable to open pcap file!\n\n"
# define ERRFILELEN	"<output_file_name> cannot be empty!\n\n"

# define INFO		"Execute as follows:\n\n\t./PackReader <file.pcap> <output_file_name>\n\n"

//* Utils
size_t	ft_strlen(char *s);
size_t	ft_putstr(int fd, char *s);
char	*ft_strdup(char *s);
int		ft_strcmp(char *s1, char *s2);
int		cmpExt(char *arg, char *diff);
char	*ft_strjoin(char *s1, char *s2);
char	*num_str_gen( size_t n );
void	*free_all(int num, ...);

#endif