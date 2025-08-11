#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

char	**get_all_folders();

int main()
{
	char	**paths;
	size_t	i;

	i = 0;
	paths = get_all_folders();
	while (paths[i])
	{
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
	int		star;

	star = 0;
	i =  0;
	while(1)
	{
		if (match[j] == '*')
			star = 1;
		while (star == 0 && str[i] == match[j])
		{
			i ++;
			j++;
		}



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
	printf("%s\n", str);
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
