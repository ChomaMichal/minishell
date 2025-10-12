/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:26:29 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/12 22:24:44 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdint.h>

/* FROM JOSEF'S LIBFT */
// void	btree_apply_prefix(t_btree *root, void (*applyf)(void *));
// void	btree_apply_infix(t_btree *root, void (*applyf)(void *));
// void	btree_apply_suffix(t_btree *root, void (*applyf)(void *));

char	**ft_append_arr_str(char ***arr, char *str);
size_t	ft_arrlen(void **arr);
int		ft_atoi(const char *nptr);
long	ft_atoi_but_better(const char *nptr);
int		ft_hextoi_base(char *str, char *base);

void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_coppyarrstr(char **arr);
void	free_arr(void ***arr);
void	free_split(char **arr);
char	*ft_get_env_value(char **arr, char *key);
int		ft_isalnum(int str);
int		ft_isalpha(int c);
int		ft_isdigit(int str);
char	*ft_itoa(int n);
int		ft_printf(int fd, const char *format, ...);
size_t	ft_putstr_fd(char *s, int fd);
void	ft_putstrerr(char *str);
char	**ft_split_dels(char const *s, char *delimiter);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinf1(char *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strsjoin(char const *s1, char const *s2, char const *s3);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstrerr(char *str);

// STOP
// int		ft_atoi(const char *nptr);
// long	ft_atoi_but_better(const char *nptr);

// int		ft_printf(int fd, const char *format, ...);

// char	**ft_split_dels(char const *s, char *delimiter);


// /* END "FROM" */

// void	set_rt(int *rt, int num);
// size_t	ft_arrlen(void **arr);
// char	*ft_get_env_value(char **arr, char *key);
// char	**ft_append_arr_str(char ***arr, char *str);
// char	**ft_coppyarrstr(char **arr);
// char	**ft_split(char const *s, char c);
// size_t	ft_strlcat(char *dst, const char *src, size_t size);
// void	*ft_memmove(void *dst, const void *src, size_t n);
// int		ft_memcmp(const void *s1, const void *s2, size_t n);
// void	*ft_calloc(size_t nmemb, size_t size);
// int		ft_atoi(const char *nptr);
// void	ft_bzero(void *s, size_t n);
// void	*ft_memcpy(void *dest, const void *src, size_t n);
// void	*ft_memchr(const void *s, int c, size_t n);
// int		ft_toupper(int c);
// int		ft_tolower(int c);
// int		ft_isascii(int str);
// int		ft_isprint(int str);
// char	*ft_strrchr(const char *s, int c);
// void	*ft_memset(void *s, int c, size_t n);
// char	*ft_strtrim(char const *s1, char const *set);
// char	*ft_itoa(int n);
// void	ft_putstr_fd(char *s, int fd);
// char	*ft_strmapi(char *s, char (*f)(unsigned int, char*));
// void	ft_striteri(char *s, void (*f)(unsigned int,char*));
// char	**ft_split(char const *s, char c);
// void	ft_putchar_fd(char c, int fd);
// void	ft_putnbr_fd(int n, int fd);
// // takes adress null terminated pointer to array of malloced pointers 
// // frees all pointers in array and the pointer of the master array and sets it to NULL
// void	free_arr(void ***arr);

#endif
