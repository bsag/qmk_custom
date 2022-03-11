#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "oneshot.h"

// Layer keys
#define NUM OSL(_NUM)
#define SYM OSL(_SYM)
#define WNAV MO(_WNAV) // Workspace navigation and media
#define FUN MO(_FUN) // Fkeys and mods only
#define NAV_SPC LT(_NAV, KC_SPC)

// shortcuts
#define M_UNDO G(KC_Z)
#define M_CUT G(KC_X)
#define M_COPY G(KC_C)
#define M_PSTE G(KC_V)
#define M_SAVE G(KC_S)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define ALF LGUI(KC_SPC)
#define HOOK HYPR(KC_H)
// window resizing shortcuts
// left, right, full
#define LHLF HYPR(KC_J)
#define RHLF HYPR(KC_L)
#define FULL HYPR(KC_K)
// workspace shortcuts
#define W1 HYPR(KC_1)
#define W2 HYPR(KC_2)
#define W3 HYPR(KC_3)
#define W4 HYPR(KC_4)
#define W5 HYPR(KC_5)
#define W6 HYPR(KC_6)
// to qwerty layer
#define TG_QWTY TG(_DEF)
// awkward symbols to type
#define GBPD LALT(KC_3) // UK pound sign
#define PMIN LALT(KC_PLUS) // plus/minus symbol

enum layers {
	_BKL,
	_DEF,
	_NUM,
	_SYM,
	_NAV,
	_WNAV,
	_FUN,
};

enum keycodes {
	// Custom oneshot mod implementation with no timers.
	OS_SHFT = SAFE_RANGE,
	OS_CTRL,
	OS_ALT,
	OS_CMD,

	NUMWORD,

	CLEAR,

	SW_APP,
};
