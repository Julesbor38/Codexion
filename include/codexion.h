/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbordeli <jbordeli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:03:51 by jbordeli          #+#    #+#             */
/*   Updated: 2026/05/04 13:34:56 by jbordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>


typedef enum e_scheduler
{
    FIFO,
    EDF
}   t_scheduler;

typedef struct s_sim
{
    int nb_coders;
    long time_to_burnout;
    long time_to_compil;
    long time_to_debug;
    long time_to_refactor;
    int required_compiles;
    long dongle_cooldown;
    t_scheduler scheduler;
}   t_sim;
// Parsing
int is_positive_number(char *str);
int fill_sim(char **argv, t_sim *sim);
int parse_args(int argc, char **argv, t_sim *sim);
int def_args(int argc, char **argv);
// dongles
void    *routine(void *arg);

#endif
