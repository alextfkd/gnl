/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:35:47 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/22 22:02:24 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(char *s, int st, int ed)
{
	char	*res;
	int		i;

	if (s == NULL)
		return (NULL);
	if (ed == -1)
		ed = gnl_strlen(s) - 1;
	if (st > ed)
		return (ft_strndup("", 0, 0));
	res = (char *)malloc(ed - st + 2);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < ed - st + 1)
	{
		res[i] = s[st + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*pop_new_line(t_carry *head)
{
	char	*res;
	char	*new_carry;
	int		i;

	i = 0;
	if (head == NULL)
		return (NULL);
	if (head->len == 0)
		return (NULL);
	if (head->txt == NULL)
		return (NULL);
	while (head->txt[i] != '\0' && head->txt[i] != '\n')
		i++;
	if (head->eof == FALSE && head->txt[i] == '\0')
		return (NULL);
	res = ft_strndup(head->txt, 0, i);
	new_carry = ft_strndup(head->txt, i + 1, -1);
	free(head->txt);
	head->txt = new_carry;
	head->len -= i;
	return (res);
}

// Return NULL if len < 0, t_read_resp(fd, len, NULL) if len == 0.
t_read_resp	*ft_read(int fd)
{
	t_read_resp	*response;
	char		buf[BUFFER_SIZE];
	ssize_t		len;

	len = read(fd, buf, BUFFER_SIZE);
	if (len < 0 || len > BUFFER_SIZE)
		return (NULL);
	response = (t_read_resp *)malloc(sizeof(t_read_resp));
	if (response == NULL)
		return (NULL);
	response->fd = fd;
	response->len = len;
	if (len == 0)
	{
		response->eof = TRUE;
		response->txt = NULL;
		return (response);
	}
	response->eof = FALSE;
	response->txt = ft_strndup(buf, 0, len - 1);
	if (response->txt == NULL)
		return (free(response), NULL);
	return (response);
}

char	*clear_carry(t_carry **carry)
{
	if (*carry == NULL)
		return (NULL);
	if ((*carry)->txt != NULL)
	{
		free((*carry)->txt);
		(*carry)->txt = NULL;
		free(*carry);
		*carry = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_carry	*carry;
	t_read_resp		*response;
	char			*res;

	if (carry == NULL)
		carry = create_new_carry(fd);
	while (carry)
	{
		response = ft_read(fd);
		if (response == NULL)
			return (clear_carry(&carry));
		append_carry(carry, response);
		if (carry->eof == TRUE)
			break ;
		res = pop_new_line(carry);
		if (res != NULL)
			return (res);
	}
	res = pop_new_line(carry);
	if (res == NULL)
		return (clear_carry(&carry));
	if (res[0] == '\0' && carry->eof == TRUE)
		return (free(res), clear_carry(&carry));
	return (res);
}
