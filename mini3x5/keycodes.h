#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "oneshot.h"

// Layer keys
#define LMOD OSL(_LMOD)
#define RMOD OSL(_RMOD)
#define WNAV MO(_WNAV)
#define FUN OSL(_FUN)
#define NAV_SPC LT(_NAV, KC_SPC)
// base layer shift keys
#define SH_L LSFT_T(KC_Z)
#define SH_R RSFT_T(KC_SLSH)
// Beakl layer shift keys
#define SHL_B LSFT_T(KC_J)
#define SHR_B RSFT_T(KC_V)

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
// awkward symbols to type
#define GBPD LALT(KC_3) // UK pound sign
#define PMIN LALT(KC_PLUS) // plus/minus symbol

enum layers {
	_DEF,
	_BKL,
	_NUM,
	_NAV,
	_LMOD,
	_RMOD,
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

	CANCEL,
	CLEAR,

	SW_APP,
};
