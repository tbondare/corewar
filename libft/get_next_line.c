/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 16:20:53 by tbondare          #+#    #+#             */
/*   Updated: 2018/09/08 20:22:31 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_cnt_strct(t_lst **fr, const int fd, t_lst **crnt, size_t *i)
{
	if (*fr == NULL)
	{
		if (!(*fr = (t_lst*)malloc(sizeof(t_lst))))
			return (0);
		if (!((*fr)->var = ft_strnew((size_t)0)))
			return (0);
		(*fr)->fd = fd;
		(*fr)->next = NULL;
	}
	*crnt = *fr;
	while ((*crnt)->fd != fd && (*crnt)->next)
		*crnt = (*crnt)->next;
	if ((*crnt)->fd != fd)
	{
		if (!((*crnt)->next = (t_lst*)malloc(sizeof(t_lst))))
			return (0);
		if (!((*crnt)->next->var = ft_strnew((size_t)0)))
			return (0);
		(*crnt)->next->fd = fd;
		(*crnt)->next->next = NULL;
		*crnt = (*crnt)->next;
	}
	while ((*crnt)->var[*i] != '\n' && (*crnt)->var[*i])
		(*i)++;
	return (1);
}

static	int		for_del(char **line, t_lst **crnt, t_lst **fr)
{
	t_lst *fordel;

	if (ft_strlen((*crnt)->var) != 0)
	{
		*line = (*crnt)->var;
		IF_NU(((*crnt)->var = ft_strnew((size_t)0)));
		return (1);
	}
	fordel = *fr;
	if ((*fr)->fd == (*crnt)->fd)
		*fr = (*crnt)->next;
	else
	{
		while (fordel->next != *crnt)
			fordel = fordel->next;
		fordel->next = (*crnt)->next;
	}
	free((*crnt)->var);
	free(*crnt);
	IF_NU((*line = ft_strnew((size_t)0)));
	return (0);
}

static	int		ft_bf_not_n(size_t *b, t_param param, char *buf, const int fd)
{
	char	*temp;
	char	*str;
	int		res;

	IF_NU((temp = ft_strnew(*b)));
	temp = ft_memcpy(temp, buf, *b);
	IF_NU((str = ft_strjoin(param.crnt->var, temp)));
	free(temp);
	free(param.crnt->var);
	IF_NU((param.crnt->var = ft_strnew((size_t)0)));
	res = get_next_line(fd, param.line);
	temp = *(param.line);
	if (res == 1 || res == 0)
		IF_NU((*(param.line) = ft_strjoin(str, temp)));
	free(temp);
	free(str);
	if (res == -1)
		return (-1);
	return (1);
}

static	int		ft_g_n_l(const int fd, t_param param, t_lst **fr, size_t arr[2])
{
	char	buf[BUFF_SIZE];

	ft_memset(buf, 0, BUFF_SIZE);
	arr[1] = read(fd, buf, BUFF_SIZE);
	if (arr[1] == 0)
	{
		IF_O(for_del(param.line, &param.crnt, fr));
		return (0);
	}
	while (buf[arr[0]] != '\n' && arr[0] < arr[1])
		arr[0]++;
	if (buf[arr[0]] == '\n' && arr[0] != arr[1])
	{
		IF_NU((param.str = ft_strsub(buf, 0, arr[0])));
		IF_NU((*param.line = ft_strjoin(param.crnt->var, param.str)));
		free(param.str);
		if (arr[1] >= arr[0]++)
		{
			free(param.crnt->var);
			IF_NU((param.crnt->var = ft_strsub(buf, arr[0], arr[1] - arr[0])));
		}
		return (1);
	}
	IF_MO(ft_bf_not_n(&arr[1], param, buf, fd));
	return (1);
}

/*
** arr[0] - i & arr[1] - b & arr[2] - res
*/

int				get_next_line(const int fd, char **line)
{
	static t_lst	*fr = NULL;
	char			*s;
	size_t			ar[2];
	t_param			pr;

	pr.line = line;
	ar[0] = 0;
	if (fd < 0 || !line || BUFF_SIZE <= 0 || read(fd, "", 0) ||
			!(ft_cnt_strct(&fr, fd, &pr.crnt, &ar[0])))
		return (-1);
	if (pr.crnt->var[ar[0]] == '\n')
	{
		IF_NU((*line = ft_strsub(pr.crnt->var, 0, ar[0])));
		if (ft_strlen(pr.crnt->var) >= ar[0]++)
		{
			s = pr.crnt->var;
			IF_NU((pr.crnt->var = ft_strsub(s, ar[0], ft_strlen(s) - ar[0])));
			free(s);
		}
		return (1);
	}
	ar[0] = 0;
	IF_N((pr.res = ft_g_n_l(fd, pr, &fr, ar)));
	IF_MO(pr.res);
	return (1);
}
