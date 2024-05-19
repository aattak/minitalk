/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:47:34 by aattak            #+#    #+#             */
/*   Updated: 2024/05/15 15:31:57 by aattak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_message	g_message;

void	ft_putnbr(int nbr)
{
	char	c;

	if (nbr > 9)
		ft_putnbr(nbr / 10);
	c = (nbr % 10) + '0';
	write(1, &c, 1);
}

void	server_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_message.n_bits != 0 && g_message.last_sender != info->si_pid)
		g_message.n_bits = 0;
	if (signum == SIGUSR1)
		g_message.byte = (g_message.byte << 1) | 1;
	else
		g_message.byte <<= 1;
	g_message.n_bits++;
	if (g_message.n_bits < 8)
		g_message.flag = 1;
	g_message.last_sender = info->si_pid;
}

void	signal_checker(void)
{
	while (1)
	{
		if (g_message.flag)
		{
			g_message.flag = 0;
			kill(g_message.last_sender, SIGUSR1);
		}
		else if (g_message.n_bits == 8)
		{
			if (g_message.byte)
			{
				write(1, &g_message.byte, 1);
				g_message.n_bits = 0;
				kill(g_message.last_sender, SIGUSR1);
			}
			else
			{
				write(1, "\n", 1);
				g_message.n_bits = 0;
				kill(g_message.last_sender, SIGUSR2);
			}
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = server_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL))
	{
		write(1, "Sigaction Failure!\n", 19);
		return (1);
	}
	write(1, "Server PID : ", 13);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal_checker();
}
