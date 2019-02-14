/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:39:34 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 02:35:52 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*ft_strjointab(char **arr, char sep)
{
	int		i;
	int		len;
	char	*result;
	char	sepp[2];

	i = -1;
	len = 0;
	sepp[0] = sep;
	sepp[1] = '\0';
	if (arr == NULL || !arr[0])
		return (ft_strdup(sepp));
	while (arr[++i])
		len += ft_strlen(arr[i]);
	len += i;
	if (!(result = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		ft_strcat(result, sepp);
		ft_strcat(result, arr[i]);
	}
	return (result);
}
