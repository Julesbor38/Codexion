/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:05:57 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/05 22:35:03 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/codexion.h"

int ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while(str1[i] && str2[i])
    {
        if (str1[i] != str2[i])
            return (str1[i] - str2[i]);
        i++;
    }
    return (str1[i] - str2[i]);
}
int is_positive_number(char *str)
{
    int i;

    i = 0;
    if ((strlen(str) >= 11 && ft_strcmp(str, "-2147483648") > 0 && str[0] == '-' )|| (strlen(str) >= 10 && ft_strcmp(str, "2147483647") > 0 && str[0] != '-'))
        return (1);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    if (atoi(str) <= 0)
        return 1;
    return (0);
    
}
int    fill_data(char **argv, t_data *data)
{
    struct timeval tv;
    long start_time;
    
    gettimeofday(&tv, NULL);
    start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    data->nb_coders = atoi(argv[1]);
    data->time_to_burnout = atoi(argv[2]);
    data->time_to_compil = atoi(argv[3]);
    data->time_to_debug = atoi(argv[4]);
    data->time_to_refactor = atoi(argv[5]);
    data->required_compiles = atoi(argv[6]);
    data->dongle_cooldown = atoi(argv[7]);
    data->start_time = start_time;
    data->stop = 0;
    if(strcmp(argv[8], "fifo") == 0)
    {
            data->scheduler = FIFO;
            return 0;
    }
    else if(strcmp(argv[8], "edf") == 0)
    {
        data->scheduler = EDF;
        return 0;
    }
    return (1);
}
int parse_args(int argc, char **argv, t_data *data)
{
    int i;

    i = 1;
    if (argc != 9)
        {
            printf("Error, wrong number of arguments, it should be 9\n");
            return (1);
        }
    while(i < 8)
    {
        if (is_positive_number(argv[i]) == 1)
        {
            printf("Error, argument %d should only take numeric parameter and be > 0\n", i);
            return (1);
        };
        i++;
    }
    return(fill_data(argv, data));
}

int def_args(int argc, char **argv)
{
    t_data data;


	if (parse_args(argc, argv, &data) != 0)
	{
		printf("Parsing failed\n");
		return (1);
	}
    
	printf("Parsing OK\n");
	printf("nb_coders: %d\n", data.nb_coders);
	printf("time_to_burnout: %ld\n", data.time_to_burnout);
	printf("time_to_compile: %ld\n", data.time_to_compil);
	printf("time_to_debug: %ld\n", data.time_to_debug);
	printf("time_to_refactor: %ld\n", data.time_to_refactor);
	printf("required_compiles: %d\n", data.required_compiles);
	printf("dongle_cooldown: %ld\n", data.dongle_cooldown);
    printf("starting_time is %ld\n", data.start_time);
	if (data.scheduler == FIFO)
		printf("scheduler: FIFO\n");
	else if (data.scheduler == EDF)
		printf("scheduler: EDF\n");
    else
    {
        printf("Parsing failed\n");
        return (1);
    }
	return (0);
}