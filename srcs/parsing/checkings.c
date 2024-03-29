/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:08:21 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/31 05:35:05 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_in_charset(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	set_player(char c, int i, int j, t_game *game)
{
	game->start_direction = c;
	game->map->start_direction = c;
	game->player->pos.x = j + 0.5;
	game->player->pos.y = i + 0.5;
	if (c == 'N')
		game->player->angle = PI / 4;
	else if (c == 'S')
		game->player->angle = 3 * PI / 2;
	else if (c == 'E')
		game->player->angle = 2 * PI;
	else if (c == 'W')
		game->player->angle = PI;
}

int	check_one(t_game *game, int i, int j, int *player_count)
{
	if (i == 0 || i == game->length - 1 || j == 0 || j == game->width - 1)
		return (ft_in_charset("12", game->map->map[i][j]));
	if (game->map->map[i][j] == '2')
		return (ft_in_charset("12", game->map->map[i + 1][j])
			&& ft_in_charset("12", game->map->map[i][j + 1]));
	else if (game->map->map[i][j] == '0')
		return (ft_in_charset("01NSEW", game->map->map[i + 1][j])
			&& ft_in_charset("01NSEW", game->map->map[i][j + 1]));
	else if (ft_in_charset("NSEW", game->map->map[i][j]))
	{
		set_player(game->map->map[i][j], i, j, game);
		(*player_count)++;
		return (ft_in_charset("01", game->map->map[i + 1][j])
			&& ft_in_charset("01", game->map->map[i][j + 1]));
	}
	return (1);
}

int	check_map(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (!ft_in_charset("012NSEW", game->map->map[i][j]))
				return (0);
			if (!check_one(game, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
