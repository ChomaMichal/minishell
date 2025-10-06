/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:50:27 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 21:05:10 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	counter;
	size_t	counter2;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	counter = 0;
	counter2 = 0;
	while (s1 && s1[counter])
	{
		str[counter] = s1[counter];
		counter ++;
	}
	while (s2 && s2[counter2])
	{
		str[counter2 + counter] = s2[counter2];
		counter2 ++;
	}
	str[counter2 + counter] = 0;
	return (str);
}

char	*ft_strsjoin(char const *s1, char const *s2, char const *s3)
{
	char	*res;
	size_t	len;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	len = len1 + len2 + len3;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len + 1);
	ft_strlcpy(res + len1, s2, len + 1);
	ft_strlcpy(res + len1 + len2, s3, len + 1);
	return (res);
}