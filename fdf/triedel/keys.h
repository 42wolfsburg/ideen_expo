/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:01:03 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 13:21:05 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

// platform independent keycodes
# ifdef LINUX
// #  include <X11/keysym.h>
// #  define XK_LEFT			XK_Left
// #  define XK_RIGHT			XK_Right
// #  define XK_DOWN			XK_Down
// #  define XK_UP				XK_Up
// #  define XK_A				XK_a
// #  define XK_C				XK_c
// #  define XK_D				XK_d
// #  define XK_W				XK_w
// #  define XK_R				XK_r
// #  define XK_S				XK_s
// #  define XK_M				XK_m
// #  define XK_N				XK_n
// #  define XK_V				XK_v
// #  define XK_X				XK_x
// #  define XK_ESCAPE			XK_Escape
// #  define XK_SPACE			XK_space
// #  define XK_SHIFT_L		XK_Shift_L
// #  define XK_SHIFT_R		XK_Shift_R
#  define XK_LEFT			65361
#  define XK_RIGHT			65363
#  define XK_DOWN			65364
#  define XK_UP				65362
#  define XK_A				97
#  define XK_C				99
#  define XK_D				100
#  define XK_W				119
#  define XK_R				114
#  define XK_S				115
#  define XK_M				109
#  define XK_N				110
#  define XK_V				118
#  define XK_X				120
#  define XK_ESCAPE			65307
#  define XK_SPACE			32
#  define XK_SHIFT_L		65505
#  define XK_SHIFT_R		65506
# else
#  define XK_LEFT			123
#  define XK_RIGHT			124
#  define XK_DOWN			125
#  define XK_UP				126
#  define XK_A				0
#  define XK_C				8
#  define XK_D				2
#  define XK_W				13
#  define XK_R				15
#  define XK_S				1
#  define XK_M				46
#  define XK_N				45
#  define XK_V				9
#  define XK_X				7
#  define XK_ESCAPE			53
#  define XK_SPACE			49
#  define XK_SHIFT_L		257
#  define XK_SHIFT_R		258
# endif

// platform independent events and event masks
# ifdef LINUX

#  include <X11/X.h>
#  define NOEVENTMASK		NoEventMask
#  define KEYPRESSMASK		KeyPressMask
#  define SHIFTMASK			ShiftMask
#  define KEYRELEASEMASK	KeyReleaseMask

#  define KEYPRESS			KeyPress
#  define KEYRELEASE		KeyRelease
#  define BUTTONPRESS		ButtonPress
#  define BUTTONRELEASE		ButtonRelease
#  define BUTTONPRESSMASK	ButtonPressMask
#  define BUTTONRELEASEMASK	ButtonReleaseMask
#  define DESTROYNOTIFY		DestroyNotify

# else

#  define NOEVENTMASK		0L
#  define KEYPRESSMASK		1
#  define SHIFTMASK			1
#  define KEYRELEASEMASK	2

#  define KEYPRESS			2
#  define KEYRELEASE		3
#  define BUTTONPRESS		4
#  define BUTTONRELEASE		5
#  define BUTTONPRESSMASK	4
#  define BUTTONRELEASEMASK	8
#  define DESTROYNOTIFY		17

# endif

#endif