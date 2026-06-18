/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:05:52 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 14:39:35 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/// keyboard configuration
# include <X11/keysym.h>
# define KEY_FORWARD		XK_w
# define KEY_BACKWARD		XK_s
# define KEY_SLIDELEFT		XK_a
# define KEY_SLIDERIGHT		XK_d
# define KEY_LEFT			XK_Left
# define KEY_RIGHT			XK_Right
# define KEY_UP				XK_Up
# define KEY_DOWN			XK_Down
# define KEY_JUMP			XK_space
# define KEY_MOVEUP			KEY_JUMP
# define KEY_MOVEDOWN		XK_n
# define KEY_MOVEUP2		XK_e
# define KEY_MOVEDOWN2		XK_q
# define KEY_MINIMAP		XK_m
# define KEY_DEBUG			XK_k
# define KEY_MATRIXMODE		XK_0
# define KEY_PAUSE			XK_p
# define KEY_EXIT1			XK_Escape
# define KEY_EXIT2			XK_x
# define KEY_PHYSICS		XK_c
# define KEY_INTERACT		XK_f

// ===== gameplay =====
/// vertical movement speed
# define SPEED_MOVEVERT		.1
# define ROT_SPEED			.1
/// health below which health regen starts
# define HEALTH_REGEN_LIMIT	50
/// health regen rate (per tick)
# define HEALTH_REGEN_RATE	.015
/// if distance to agent is below this, agent will attack
# define AGENT_ATTACK_RANGE	.5
# define AGENT_ATTACK_DMG	.5
# define AGENT_SPD			.05

// game resolution
# define GAME_W				2880
# define GAME_H				1620

# define MINIMAP_TLX		0
# define MINIMAP_TLY		0
# define MINIMAP_BRX		500
# define MINIMAP_BRY		500
# define MINIMAP_SCALE		.02

// ===== graphics =====
/// height of perspective (=eye height)
# define CAM_HEIGHT			.5
/// camera width
# define CAM_WIDTH			.0001

# define FRAMERATE			40 // framerate at which upscaling starts
# define MAX_FRAMERATE		60
# define MAX_UPSCALE		1

# define MAP_DEFAULT			"lvl/level0.cub"
# define MAP_SUFFIX			".cub"

# define RAY_MARCH_DELTA	.001

// ===== matrix mode parameters =====
// matrix mode toggling
# define MATMODE_TOGGLE_SPEED	.05
# define MATMODE_MAXMIX			.85
// matrix texture
# define MATTEX_SIZE		512
# define MATTEX_SYMS		35
# define MATTEX_FADE		.6
# define MATTEX_PERIOD		6
# define MATTEX_BACK		0x001000
# define MATTEX_WHITE		0x909090

# define DISPLAY_TITLE		"cub3D"
# define TEX_NOTFOUND		"assets/404.xpm"

# define MOUSE_SENS_X		1
# define MOUSE_SENS_Y		1.5

// rendering options
# define MAX_OBJECTS		128
# define MAXHITS			32

# define DOOR_MAXOPEN		90
# define DOOR_OPENSPEED		6
# define DOOR_CLOSESPEED	4

// physics and view
# define PH_GRAVITY			.005
# define PH_JUMP			.06
# define PH_JUMP2			.12

# define CTRANSPARENT		0xff000000
# define CWHITE				0x00ffffff
# define CBLACK				0x00000000
# define CGREEN				0x004df84a
# define CRED				0x00a00000
# define CBLUE				0x0000a000
# define CGRAY				0x00d3d3d3

/// default text color
# define CTEXT				CWHITE
/// minimap view color
# define CMINIMAPDIR		CWHITE
/// intro background color
# define CINTROBG			0x00101010

# ifndef BONUS
#  define BONUS				1
# endif

// MANDATORY configuration
# if !BONUS

#  define THREADS			0
#  define ROTX				0
#  define MATTEX			0
#  define FLOOR_TEXTURE		0
/// upscale factor
#  define GAME_UPSCALE		8

// BONUS configuration
# else

#  define THREADS			12
#  define ROTX				1
#  define MATTEX			0
#  define FLOOR_TEXTURE		1
/// upscale factor
#  define GAME_UPSCALE		2

# endif

#endif
