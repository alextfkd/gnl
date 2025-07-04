/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:37:27 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/07/04 10:42:04 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	len;
	char	*p;

	len = 0;
	if (s == NULL)
		return (len);
	p = s;
	while (*p != '\0')
	{
		len++;
		p++;
	}
	return (len);
}

// Need to free s1 & s2 at the outside of this func.
char	*gnl_strjoin(char *s1, char *s2)
{
	char	*arr;
	char	*p1;
	char	*p2;
	size_t	i;

	p1 = s1;
	p2 = s2;
	arr = (char *)malloc(sizeof(char) * (gnl_strlen(p1)+ gnl_strlen(p2) + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	if (p1 != NULL)
		while (*p1 != '\0')
			arr[i++] = *p1++;
	if (p2 != NULL)
		while (*p2 != '\0')
			arr[i++] = *p2++;
	arr[i] = '\0';
	return (arr);
}

// Create new carry from resp and append to the tail of the list.
t_carry	*create_new_carry(int fd)
{
	t_carry	*new_carry;
	char	*txt;

	new_carry = (t_carry *)malloc(sizeof(t_carry));
	if (new_carry == NULL)
		return (NULL);
	txt = (char *)malloc(1);
	if (txt == NULL)
		return (free(new_carry), NULL);
	txt[0] = '\0';
	new_carry->fd = fd;
	new_carry->len = 0;
	new_carry->txt = txt;
	new_carry->eof = I_FALSE;
	new_carry->next = NULL;
	return (new_carry);
}

// This func refresh head, free(read_resp) inside this func.
t_carry	*append_carry(t_carry *head, t_read_resp *read_resp)
{
	char	*new_txt;

	if (head == NULL)
		return (NULL);
	if (read_resp->txt == NULL)
		head->eof = I_TRUE;
	new_txt = gnl_strjoin(head->txt, read_resp->txt);
	head->len += read_resp->len;
	if (head->txt != NULL)
	{
		free(head->txt);
		head->txt = new_txt;
	}
	if (read_resp->txt != NULL)
	{
		free(read_resp->txt);
		read_resp->txt = NULL;
	}
	free(read_resp);
	read_resp = NULL;
	return (head);
}
