/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:36:13 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/07/04 10:41:00 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# elif BUFFER_SIZE > 4048
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 4048
# endif

# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define I_TRUE 1
# define I_FALSE 0

typedef struct s_carry
{
	int				fd;
	ssize_t			len;
	char			*txt;
	int				eof;
	struct s_carry	*next;
}	t_carry;

typedef struct s_read_resp
{
	int		fd;
	ssize_t	len;
	char	*txt;
	int		eof;
}	t_read_resp;

t_carry		*append_carry(t_carry *head, t_read_resp *read_resp);
t_carry		*create_new_carry(int fd);
char		*clear_carry(t_carry **carry);
t_read_resp	*ft_read(int fd);
char		*gnl_strjoin(char *s1, char *s2);
char		*ft_strndup(char *s, int st, int ed);
char		*get_next_line(int fd);
size_t		gnl_strlen(char *s);
char		*pop_new_line(t_carry *head);

#endif
