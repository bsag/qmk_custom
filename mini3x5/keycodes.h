#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"

// home row mods for Platinum Hands Down
#define HHOME_R LCTL_T(KC_R)
#define HHOME_S LALT_T(KC_S)
#define HHOME_N LGUI_T(KC_N)
#define HHOME_T LSFT_T(KC_T)

#define HHOME_A RSFT_T(KC_A)
#define HHOME_E RGUI_T(KC_E)
#define HHOME_C LALT_T(KC_C)
#define HHOME_I RCTL_T(KC_I)

// home row mods for QWERTY
#define QHOME_A LCTL_T(KC_A)
#define QHOME_R LALT_T(KC_R)
#define QHOME_S LGUI_T(KC_S)
#define QHOME_T LSFT_T(KC_T)

#define QHOME_N RSFT_T(KC_N)
#define QHOME_E LGUI_T(KC_E)
#define QHOME_I LALT_T(KC_I)
#define QHOME_O RCTL_T(KC_O)

// Layer keys
#define NUM LT(_NUM, KC_ESC)
#define FUN LT(_FUN, KC_ENT)
#define NAV_BSPC LT(_NAV, KC_BSPC)

// Hands Down only
#define NAV_L LT(_NAV, KC_L)

// shortcuts
#define M_UNDO G(KC_Z)
#define M_CUT G(KC_X)
#define M_COPY G(KC_C)
#define M_PSTE G(KC_V)
#define M_SAVE G(KC_S)
#define M_DUP G(KC_D)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define WS_L A(S(KC_LEFT))
#define WS_R A(S(KC_RIGHT))
#define LAU LGUI(KC_SPC)
#define CC C(KC_C)
// to colemak layer
#define TG_CDH TG(_CDH)
// to hands down layer
#define TG_PHD TG(_PHD)
// awkward symbols to type
#define GBPD LALT(KC_3) // UK pound sign
#define PMIN LALT(KC_PLUS) // plus/minus symbol

enum layers {
    _CDH,
	_PHD,
	_NUM,
	_NAV,
	_FUN,
};

enum keycodes {
	// Numword and switch app
	NUMWORD = SAFE_RANGE,
	SW_APP,
};
