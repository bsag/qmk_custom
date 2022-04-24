#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"

// home row mods for Platinum Hands Down
#define HHOME_R LSFT_T(KC_R)
#define HHOME_S LCTL_T(KC_S)
#define HHOME_N LALT_T(KC_N)
#define HHOME_T LGUI_T(KC_T)

#define HHOME_A RGUI_T(KC_A)
#define HHOME_E LALT_T(KC_E)
#define HHOME_C RCTL_T(KC_C)
#define HHOME_I RSFT_T(KC_I)

// home row mods for QWERTY
#define QHOME_A LSFT_T(KC_A)
#define QHOME_S LCTL_T(KC_S)
#define QHOME_D LALT_T(KC_D)
#define QHOME_F LGUI_T(KC_F)

#define QHOME_J RGUI_T(KC_J)
#define QHOME_K LALT_T(KC_K)
#define QHOME_L RCTL_T(KC_L)
#define QHOME_QUOT RSFT_T(KC_QUOT)

// Layer keys
#define NUM LT(_NUM, KC_ESC)
#define SYM LT(_SYM, KC_ENT)
#define WNAV MO(_WNAV) // Workspace navigation and media
#define FUN MO(_FUN) // Fkeys and mods only
#define NAV_SPC LT(_NAV, KC_SPC)

// Hands Down only
#define NAV_L LT(_NAV, KC_L)

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
// to hands down layer
#define TG_PHD TG(_PHD)
// awkward symbols to type
#define GBPD LALT(KC_3) // UK pound sign
#define PMIN LALT(KC_PLUS) // plus/minus symbol

enum layers {
	_PHD,
	_DEF,
	_NUM,
	_SYM,
	_NAV,
	_WNAV,
	_FUN,
};

enum keycodes {
	// Numword and switch app
	NUMWORD = SAFE_RANGE,
	SW_APP,
};
