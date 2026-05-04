/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:05:57 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/04 16:10:59 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/codexion.h"


int is_positive_number(char *str)
{
    long result;
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    result = atoi(str);
    if (result <= 0)
        return 1;
    return (0);
    
}
int    fill_sim(char **argv, t_sim *sim)
{
    sim->nb_coders = atoi(argv[1]);
    sim->time_to_burnout = atoi(argv[2]);
    sim->time_to_compil = atoi(argv[3]);
    sim->time_to_debug = atoi(argv[4]);
    sim->time_to_refactor = atoi(argv[5]);
    sim->required_compiles = atoi(argv[6]);
    sim->dongle_cooldown = atoi(argv[7]);
    if(strcmp(argv[8], "fifo") == 0)
    {
            sim->scheduler = FIFO;
            return 0;
    }
    else if(strcmp(argv[8], "edf") == 0)
    {
        sim->scheduler = EDF;
        return 0;
    }
    return (1);
}
int parse_args(int argc, char **argv, t_sim *sim)
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
    return(fill_sim(argv, sim));
}

int def_args(int argc, char **argv)
{
    t_sim sim;
	if (parse_args(argc, argv, &sim) != 0)
	{
		printf("Parsing failed\n");
		return (1);
	}
    
	printf("Parsing OK\n");
	printf("nb_coders: %d\n", sim.nb_coders);
	printf("time_to_burnout: %ld\n", sim.time_to_burnout);
	printf("time_to_compile: %ld\n", sim.time_to_compil);
	printf("time_to_debug: %ld\n", sim.time_to_debug);
	printf("time_to_refactor: %ld\n", sim.time_to_refactor);
	printf("required_compiles: %d\n", sim.required_compiles);
	printf("dongle_cooldown: %ld\n", sim.dongle_cooldown);
	if (sim.scheduler == FIFO)
		printf("scheduler: FIFO\n");
	else if (sim.scheduler == EDF)
		printf("scheduler: EDF\n");
    else
    {
        printf("Parsing failed\n");
        return (1);
    }

	return (0);
}