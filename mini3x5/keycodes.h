#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"

// home row mods for Colemak-DH
/* #define HOME_A LCTL_T(KC_A) */
/* #define HOME_R LALT_T(KC_R) */
/* #define HOME_S LGUI_T(KC_S) */
/* #define HOME_T LSFT_T(KC_T) */

/* #define HOME_N RSFT_T(KC_N) */
/* #define HOME_E LGUI_T(KC_E) */
/* #define HOME_I LALT_T(KC_I) */
/* #define HOME_O RCTL_T(KC_O) */

// Layer keys
#define NUM LT(_NUM, KC_ENT)
#define NAV LT(_NAV, KC_ESC)
// FUN is both together

// shortcuts
#define M_UNDO G(KC_Z)
#define M_CUT G(KC_X)
#define M_COPY G(KC_C)
#define M_PSTE G(KC_V)
#define M_SAVE G(KC_S)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define WS_L A(S(KC_LEFT))  // select word left
#define WS_R A(S(KC_RIGHT)) // select word right
#define W_L A(KC_LEFT)      // move word left
#define W_R A(KC_RIGHT)     // move word right
#define LAU LGUI(KC_SPC)    // launcher (cmd+spc)
// awkward symbols to type
#define GBPD LALT(KC_3) // UK pound sign
#define PMIN LALT(KC_PLUS) // plus/minus symbol

enum layers {
    _CDH,
	_NUM,
	_NAV,
	_FUN,
};

enum keycodes {
	// Numword and switch app
	NUMWORD = SAFE_RANGE,

	OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

	LLOCK,
	SW_APP,
};
