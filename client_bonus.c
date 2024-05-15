/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:46:32 by aattak            #+#    #+#             */
/*   Updated: 2024/05/15 16:05:06 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_flag;

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

pid_t	parse_pid(char *s_pid)
{
	long	pid;
	int		i;

	pid = 0;
	i = 0;
	while (ft_isspace(s_pid[i]))
		i++;
	while (s_pid[i] >= '0' && s_pid[i] <= '9')
	{
		pid *= 10;
		pid += s_pid[i] - '0';
		if (pid > INT_MAX)
			return (-1);
		i++;
	}
	while (ft_isspace(s_pid[i]))
		i++;
	if (s_pid[i])
		return (-1);
	return ((pid_t)pid);
}

void	client_handler(int signum)
{
	g_flag = 1;
	if (signum == SIGUSR2)
		write(1, "Message sent to server successfully!\n", 37);
}

void	send_message(pid_t s_pid, char *str)
{
	int		i;
	char	j;

	i = 0;
	while (1)
	{
		j = 8;
		while (--j >= 0)
		{
			if ((str[i] >> j) & 1)
				kill(s_pid, SIGUSR1);
			else
				kill(s_pid, SIGUSR2);
			usleep(270);
			if (!g_flag)
			{
				write(1, "CONNECTION LOST!\n", 17);
				exit (1);
			}
			g_flag = 0;
		}
		if (!str[i])
			break ;
		i++;
	}
}

int	main(int ac, char **av)
{
	pid_t				s_pid;
	struct sigaction	sa;

	if (ac != 3)
	{
		write(1, "./client <Server PID> <Message to send>\n", 40);
		return (1);
	}
	s_pid = parse_pid(av[1]);
	if (s_pid == -1 || av[2][0] == '\0')
	{
		write(1, "./client <Server PID> <Message to send>\n", 40);
		return (1);
	}
	sa.sa_handler = client_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL))
	{
		write(1, "Sigaction Failure!\n", 19);
		return (1);
	}
	send_message(s_pid, av[2]);
}
