#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

char	**get_all_folders();
int	star_match(char *match, char *str);

int main()
{
	char	**paths;
	size_t	i;

	i = 0;
	paths = get_all_folders();
	// printf("%i result\n",star_match("*.c", "main.chehe"));
	while (paths[i])
	{
		if (star_match("he*", paths[i]))
			printf("%s\n", paths[i]);
		i++;
	}
	free_arr((void ***) &paths);
	return (0);
}

int	star_match(char *match, char *str)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	int		star;
	size_t	change;

	star = 0;
	j = 0;
	i =  0;
	change = 0;
	while(1)
	{
		change = 0;
		// printf("%c char \n", str[i]);
		if (match[j] == '*')
		{
			star = 1;
			j ++;
			change = 1;
		}
		// printf("%i star\n", star);
		while (star == 0 && str[i] == match[j] && str[i] && match[j])
		{
			// printf("triggered star\n");
			i ++;
			j++;
			change = 1;
		}
		tmp = 0;
		while (star == 1 && str[i + tmp] == match[j + tmp] && str[i + tmp] && match[j + tmp] && !(match[0] == '*' && i == 0))
		{
			tmp ++;
			// printf("triggered tmp\n");
		}
		// printf("%lutmp\n", tmp);
		// printf("%lu j + tmp\n", j + tmp);
		// printf("%i match[j  + tmp]\n", match[j + tmp]);
		if ((match[j + tmp] == '*' || match[j + tmp] == 0) && tmp != 0)
		{
			j = j + tmp;
			i = i + tmp;
			star = 0;
			change = 1;
			// printf("%c str\n", str[i]);
			// printf("%c match\n", match[j]);
		}
		else if (star == 0)
		{
			i ++;
			change = 1;
		}
		// if (str[i] == 0 && (match[j] == 0 || (match[j]== '*' && match[j] == 0 )))
			// return (1);
		if (str[i] == 0 && match[j] == 0)
			return (1);
		if (str[i] != 0 && match[j] == '*' && match[j+1] == 0)
			return (1);
		if (match[j] == 0)
			return (0);
		if (str[i] == 0)
			return (0);
		if ( change == 0)
			return (0);
	}
}



char	**get_all_folders()
{
	DIR *directory;
	struct dirent	*idk;
	int i;
	char	path[PATH_MAX];
	char	*str;
	char	**arr;

	arr = NULL;
	str = getcwd(path, PATH_MAX);
	// printf("%s\n", str);
		// exit(1); // errorahnle properly
	idk = malloc(sizeof(struct dirent));
	i = 0;
	// printf("hehe\n");
	directory = opendir(str);
	// printf("hehe\n");
	// printf("%s  ", idk->d_name);
	idk = readdir(directory);
	// printf("hehe\n");
	while (idk)
	{
	// printf("hehe\n");
		str = ft_strdup(idk->d_name);
		// printf("%s\n", str);
		ft_append_arr_str(&arr, str);
		idk = readdir(directory);
	}
	ft_append_arr_str(&arr, NULL);
	free(idk);
	closedir(directory);
	return (arr);
}
