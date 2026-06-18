/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:09:49 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 15:15:04 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

long long	millitimestamp(void)
{
	struct timeval	timeval;
	long long		microtime;

	gettimeofday(&timeval, NULL);
	microtime = timeval.tv_sec * 1000LL + timeval.tv_usec / 1000;
	return (microtime);
}

mlx_image_t *show_moves(t_game *game) {
    mlx_image_t *text_img;
    char *moves;

    moves = ft_itoa(game->movements);
    if (!moves)
        return (NULL);
    text_img = mlx_put_string(game->mlx, moves, (game->map_x - 4) / 2 * 60 + 40, game->map_y * 60 + 18);
    free(moves);
    if (text_img) {
        mlx_set_instance_depth(text_img->instances, 100);
    }
    return (text_img);
}

void clear_buffer(mlx_image_t *buffer, uint32_t color) {
    if (!buffer)
        return;
    uint32_t *pixels = (uint32_t *)buffer->pixels;
    int size = buffer->width * buffer->height;
    for (int i = 0; i < size; i++) {
        pixels[i] = color;
    }
}

void copy_image_to_buffer(mlx_image_t *dest, mlx_image_t *src, int dest_x, int dest_y) {
    uint32_t *dest_pixels = (uint32_t *)dest->pixels;
    uint32_t *src_pixels = (uint32_t *)src->pixels;
    int src_width = src->width;
    int src_height = src->height;
    int dest_width = dest->width;
    int dest_height = dest->height;

    for (int y = 0; y < src_height; y++) {
        for (int x = 0; x < src_width; x++) {
            int src_index = y * src_width + x;
            int dest_index = (y + dest_y) * dest_width + (x + dest_x);

            if (x + dest_x >= 0 && x + dest_x < dest_width && y + dest_y >= 0 && y + dest_y < dest_height) {
                uint32_t src_pixel = src_pixels[src_index];
                uint32_t dest_pixel = dest_pixels[dest_index];

                // Розпаковуємо кольори та альфа-канал
                uint8_t src_a = (src_pixel >> 24) & 0xFF;
                uint8_t src_r = (src_pixel >> 16) & 0xFF;
                uint8_t src_g = (src_pixel >> 8) & 0xFF;
                uint8_t src_b = src_pixel & 0xFF;

                uint8_t dest_a = (dest_pixel >> 24) & 0xFF;
                uint8_t dest_r = (dest_pixel >> 16) & 0xFF;
                uint8_t dest_g = (dest_pixel >> 8) & 0xFF;
                uint8_t dest_b = dest_pixel & 0xFF;

                // Виконуємо альфа-змішування
                uint8_t out_a = src_a + dest_a * (255 - src_a) / 255;
                uint8_t out_r = (src_r * src_a + dest_r * dest_a * (255 - src_a) / 255) / out_a;
                uint8_t out_g = (src_g * src_a + dest_g * dest_a * (255 - src_a) / 255) / out_a;
                uint8_t out_b = (src_b * src_a + dest_b * dest_a * (255 - src_a) / 255) / out_a;

                // Збираємо назад піксель
                dest_pixels[dest_index] = (out_a << 24) | (out_r << 16) | (out_g << 8) | out_b;
            }
        }
    }
}