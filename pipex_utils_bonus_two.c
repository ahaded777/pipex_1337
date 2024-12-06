/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:49:59 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/06 11:25:14 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

int	ft_tcheck_path2(char *cmd)
{
	char	**words;
	char	*path;

	words = ft_split(cmd, ' ');
	path = ft_find_path(words[0]);
	if (!path || access(path, X_OK) == -1)
		return (0);
	free(path);
	return (1);
}

void	setup_here_doc_input_(void)
{
	int	temp_file_r;

	temp_file_r = open("/tmp/.here_doc", O_RDONLY);
	if (temp_file_r < 0)
	{
		perror("Error opening temporary file");
		exit(-1);
	}
	dup2(temp_file_r, STDIN_FILENO);
	close(temp_file_r);
}

void	setup_here_doc_input(char **argv)
{
	int		temp_file_wr;
	char	*get_line;

	temp_file_wr = open("/tmp/.here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_file_wr < 0)
	{
		perror("Error creating temporary file");
		exit(-1);
	}
	while (1)
	{
		get_line = get_next_line(0);
		if (!get_line)
			break ;
		if (ft_strncmp(get_line, argv[2],
				ft_strlen((const char *)argv[2])) == 0)
		{
			free(get_line);
			break ;
		}
		write(temp_file_wr, get_line, ft_strlen((const char *)get_line));
		free(get_line);
	}
	close(temp_file_wr);
	setup_here_doc_input_();
}

void	check_commands_and_here_doc(int argc, char **argv)
{
	int	i;

	i = 3;
	if (ft_tcheck_path2(argv[2]) == 1)
	{
		printf("Error: fin kayna stop asa7bi\n");
		exit(-1);
	}
	else
	{
		while (i < argc - 1)
		{
			if (!ft_tcheck_path2(argv[i]))
			{
				printf("Error: had lcommand makaynach %s\n", argv[i]);
				exit(-1);
			}
			i++;
		}
		setup_here_doc_input(argv);
	}
}