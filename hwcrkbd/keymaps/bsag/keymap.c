/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_steno.h"

bool is_cmd_tab_active = false; // ADD this near the begining of keymap.c
uint16_t cmd_tab_timer = 0;     // we will be using them soon.

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _PLOVER
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  PLOVER,
  EXT_PLV,
  CMD_TAB,
};

// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L) // Right alt doesn't work with M-x in Emacs
#define HOME_SC RCTL_T(KC_SCLN)

// Left-hand home row mods for Lower (number layer)
#define HOME_6 LCTL_T(KC_6)
#define HOME_7 LALT_T(KC_7)
#define HOME_8 LGUI_T(KC_8)
#define HOME_9 LSFT_T(KC_9)

// Other mod-taps for convenience of referencing
#define C_ESC LCTL_T(KC_ESC)

// Other keys for quick access to symbols
#define GBP LALT(KC_3)              // £
#define DEG LSFT(LALT(KC_8))        // °
#define PMIN LSFT(LALT(KC_EQL))     // ±
#define PTAB LSFT(LGUI(KC_LBRC))    // previous tab/buffer
#define NTAB LSFT(LGUI(KC_RBRC))    // next tab/buffer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      CMD_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      C_ESC,   HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,                         KC_H,    HOME_J,  HOME_K,  HOME_L, HOME_SC, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TAB, LOWER,  KC_SPC,     KC_ENT,   RAISE,  KC_BSPC
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      CMD_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DOT,  KC_DELETE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      C_ESC,   HOME_6,  HOME_7,  HOME_8,  HOME_9,    KC_0,                       KC_LEFT, KC_DOWN,  KC_UP,  KC_RIGHT, PTAB,   NTAB,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  KC_MINS, KC_SLSH, KC_ASTR, KC_PLUS, KC_DOT,                      HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TAB, _______,  KC_SPC,     KC_ENT, _______, KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

 [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      CMD_TAB, KC_EXLM,  KC_LT,   KC_DLR,  KC_GT,   KC_AT,                       GBP,      KC_LBRC, KC_UNDS,KC_RBRC, DEG,     KC_DELETE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      C_ESC, KC_BSLASH, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH,                     KC_PERC,  KC_LCBR, KC_EQL, KC_RCBR, KC_PIPE, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_SCLN, KC_COLN, KC_ASTR, KC_PLUS, KC_GRV,                      KC_MINS, KC_AMPR, KC_CIRC, KC_TILD,   PMIN,   KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TAB, _______,  KC_SPC,     KC_ENT, _______, KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     RESET, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,                         RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, PLOVER, KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,  KC_F6,                       KC__MUTE, KC__VOLDOWN, KC__VOLUP, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,                      HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TAB, _______,  KC_SPC,     KC_ENT, _______, KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

  [_PLOVER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     CMD_TAB, STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,                  HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), STN_ZR, HYPR(KC_5), HYPR(KC_6),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,                      STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     EXT_PLV, STN_S2,  STN_KL, STN_WL,   STN_RL,  STN_ST2,                      STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        STN_NUM,   STN_A,   STN_O,      STN_E,   STN_U,   STN_NUM
                                      //`--------------------------'  `--------------------------'
  )
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
};

//
// Layer state changed
//
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


#ifdef OLED_DRIVER_ENABLE
#include <stdio.h>

// Horizontal Corne logo
static void render_logo(void) {
  static char const corne_logo[] PROGMEM = {
    0x80, 0x81, 0x82, 0x83, 0x84,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4,
    0x63, 0x6f, 0x72, 0x6e, 0x65, 0};

  oled_write_P(corne_logo, false);
}

// Shows layer as a slice with icons
void render_layer_state(uint8_t const state) {
 static char const base_layer[] PROGMEM = {
    0x20, 0x9a, 0x9b, 0x9c, 0x20,
    0x20, 0xba, 0xbb, 0xbc, 0x20,
    0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
  static char const numb_layer[] PROGMEM = {
    0x20, 0x94, 0x95, 0x96, 0x20,
    0x20, 0xb4, 0xb5, 0xb6, 0x20,
    0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
  static char const symb_layer[] PROGMEM = {
    0x20, 0x97, 0x98, 0x99, 0x20,
    0x20, 0xb7, 0xb8, 0xb9, 0x20,
    0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
  static char const adj_layer[] PROGMEM = {
    0x20, 0x9d, 0x9e, 0x9f, 0x20,
    0x20, 0xbd, 0xbe, 0xbf, 0x20,
    0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

  switch(state) {
  case _PLOVER: oled_write_P(base_layer, false); break;
  case _ADJUST: oled_write_P(adj_layer, false); break;
  case _RAISE: oled_write_P(symb_layer, false); break;
  case _LOWER: oled_write_P(numb_layer, false); break;
  default:  oled_write_P(base_layer, false);
 }
}
static void render_gui_alt(uint8_t const gui, uint8_t const alt) {
	static char const gui_off_1[] PROGMEM = {0x85, 0x86, 0};
	static char const gui_off_2[] PROGMEM = {0xa5, 0xa6, 0};
	static char const gui_on_1[] PROGMEM = {0x8d, 0x8e, 0};
	static char const gui_on_2[] PROGMEM = {0xad, 0xae, 0};

	static char const alt_off_1[] PROGMEM = {0x87, 0x88, 0};
	static char const alt_off_2[] PROGMEM = {0xa7, 0xa8, 0};
	static char const alt_on_1[] PROGMEM = {0x8f, 0x90, 0};
	static char const alt_on_2[] PROGMEM = {0xaf, 0xb0, 0};

	// Fillers between icon frames
	static char const off_off_1[] PROGMEM = {0xc5, 0};
	static char const off_off_2[] PROGMEM = {0xc6, 0};
	static char const on_off_1[] PROGMEM = {0xc7, 0};
	static char const on_off_2[] PROGMEM = {0xc8, 0};
	static char const off_on_1[] PROGMEM = {0xc9, 0};
	static char const off_on_2[] PROGMEM = {0xca, 0};
	static char const on_on_1[] PROGMEM = {0xcb, 0};
	static char const on_on_2[] PROGMEM = {0xcc, 0};

	// Top half with in between fillers
	oled_write_P(gui ? gui_on_1 : gui_off_1, false);
	if (gui && alt) { oled_write_P(on_on_1, false); }
	else if (gui) { oled_write_P(on_off_1, false); }
	else if (alt) { oled_write_P(off_on_1, false); }
	else { oled_write_P(off_off_1, false); }
	oled_write_P(alt ? alt_on_1 : alt_off_1, false);

	// Bottom half with in between fillers
	oled_write_P(gui ? gui_on_2 : gui_off_2, false);
	if (gui && alt) { oled_write_P(on_on_2, false); }
	else if (gui) { oled_write_P(on_off_2, false); }
	else if (alt) { oled_write_P(off_on_2, false); }
	else { oled_write_P(off_off_2, false); }
	oled_write_P(alt ? alt_on_2 : alt_off_2, false);
}


static void render_ctrl_shift(uint8_t const ctrl, uint8_t const shift) {
	static char const ctrl_off_1[] PROGMEM = {0x89, 0x8a, 0};
	static char const ctrl_off_2[] PROGMEM = {0xa9, 0xaa, 0};
	static char const ctrl_on_1[] PROGMEM = {0x91, 0x92, 0};
	static char const ctrl_on_2[] PROGMEM = {0xb1, 0xb2, 0};

	static char const shift_off_1[] PROGMEM = {0x8b, 0x8c, 0};
	static char const shift_off_2[] PROGMEM = {0xab, 0xac, 0};
	static char const shift_on_1[] PROGMEM = {0xcd, 0xce, 0};
	static char const shift_on_2[] PROGMEM = {0xcf, 0xd0, 0};

	// Fillers between icon frames
	static char const off_off_1[] PROGMEM = {0xc5, 0};
	static char const off_off_2[] PROGMEM = {0xc6, 0};
	static char const on_off_1[] PROGMEM = {0xc7, 0};
	static char const on_off_2[] PROGMEM = {0xc8, 0};
	static char const off_on_1[] PROGMEM = {0xc9, 0};
	static char const off_on_2[] PROGMEM = {0xca, 0};
	static char const on_on_1[] PROGMEM = {0xcb, 0};
	static char const on_on_2[] PROGMEM = {0xcc, 0};

	// Top half with in between fillers
	oled_write_P(ctrl ? ctrl_on_1 : ctrl_off_1, false);
	if (ctrl && shift) { oled_write_P(on_on_1, false); }
	else if (ctrl) { oled_write_P(on_off_1, false); }
	else if (shift) { oled_write_P(off_on_1, false); }
	else { oled_write_P(off_off_1, false); }
	oled_write_P(shift ? shift_on_1 : shift_off_1, false);

	// Bottom half with in between fillers
	oled_write_P(ctrl ? ctrl_on_2 : ctrl_off_2, false);
	if (ctrl && shift) { oled_write_P(on_on_2, false); }
	else if (ctrl) { oled_write_P(on_off_2, false); }
	else if (shift) { oled_write_P(off_on_2, false); }
	else { oled_write_P(off_off_2, false); }
	oled_write_P(shift ? shift_on_2 : shift_off_2, false);
}

void render_keymap_status(void) {
  oled_set_cursor(0,1);

  switch (get_highest_layer(layer_state)) {
  case _PLOVER: oled_write_ln_P(PSTR("PLOVR"), false); break;
  default: oled_write_ln_P(PSTR("QWRTY"), false); break;
  }

  oled_set_cursor(0,4);
  render_layer_state(get_highest_layer(layer_state|default_layer_state));

  oled_set_cursor(0,9);
  render_gui_alt(
                 (get_mods()|get_oneshot_mods()) & MOD_MASK_GUI,
                 (get_mods()|get_oneshot_mods()) & MOD_MASK_ALT
                 );
  render_ctrl_shift(
                    (get_mods()|get_oneshot_mods()) & MOD_MASK_CTRL,
                    (get_mods()|get_oneshot_mods()) & MOD_MASK_SHIFT ||
                    host_keyboard_led_state().caps_lock
                    );
}

// Luna animation.
#define LUNA_FRAMES 2
#define LUNA_FRAME_DURATION 200 // Milliseconds per frames
#define LUNA_SIZE 96

#define NEXT(k) (k + 1) & 1
static uint8_t current_frame = 0;

static void render_luna_sit(void) {
	static char const sit[LUNA_FRAMES][LUNA_SIZE] PROGMEM = { {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xfc,
		0xfe,0xfd,0xfe,0xdc,0xfc,0xfc,0xfe,0x5d,0xfe,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xf0,0xf8,0x1c,0xf0,0xf8,0xfc,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xfd,0xf9,0xfd,0x7f,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0f,0x1f,0x1f,0x3f,0x3f,0x3f,0x37,
		0x21,0x13,0x3f,0x3f,0x3f,0x0f,0x11,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	}, {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xfe,
		0xfd,0xfe,0xfc,0xdc,0xfc,0xfe,0xfd,0x5e,0xfc,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0xe0,0xf0,0xf8,0xfc,0x80,0xf0,0xf8,0xfc,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xfd,0xf1,0xfd,0x7f,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0f,0x1f,0x1f,0x3f,0x3f,0x3f,0x37,
		0x21,0x13,0x3f,0x3f,0x3f,0x0f,0x11,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	} };

	current_frame = NEXT(current_frame);
	oled_write_raw_P(sit[current_frame], LUNA_SIZE);
}


static void render_luna_walk(void) {
	static char const walk[LUNA_FRAMES][LUNA_SIZE] PROGMEM = { {
		0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0xf0,0xf0,0x70,0x30,0x20,0x00,0x80,0xc0,
		0xc0,0xf0,0xf8,0xf4,0xf8,0x70,0xf0,0xf0,0xf8,0x74,0xf8,0x80,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x07,0x0f,0xff,0xfd,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xe7,0xf5,0x1f,0x0f,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1f,0x3f,0x3f,0x3f,0x0f,0x11,0x1f,0x1f,
		0x03,0x07,0x1f,0x3f,0x3f,0x0f,0x13,0x1f,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	}, {
		0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0xe0,0xe0,0xc0,0x80,0x00,0x00,0x00,
		0x00,0xe0,0xf0,0xe8,0xf0,0xe0,0xe0,0xe0,0xf0,0xe8,0xf0,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x1f,0x3f,0xfb,0xfd,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
		0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xef,0xcf,0xea,0x3f,0x1f,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x3f,0x0f,0x03,0x07,0x0f,0x1f,0x03,
		0x1f,0x1f,0x17,0x0f,0x1f,0x3f,0x3f,0x33,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	} };

	current_frame = NEXT(current_frame);
	oled_write_raw_P(walk[current_frame], LUNA_SIZE);
}


static void render_luna_run(void) {
	static char const run[LUNA_FRAMES][LUNA_SIZE] PROGMEM = { {
		0x00,0x00,0x00,0x00,0xe0,0xf0,0xf8,0xf8,0xf8,0xb0,0xa0,0x80,0x80,0x80,0x80,0x80,
		0x80,0xc0,0xc0,0xfc,0xf4,0xe4,0xf8,0x70,0xf8,0xe4,0xf8,0x70,0xc0,0x80,0x00,0x00,
		0x00,0x00,0x00,0x00,0x01,0x63,0xe7,0xe7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0x67,0x37,0x35,0x1f,0x0f,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x0e,0x0f,0x07,0x07,0x07,0x07,0x03,0x03,0x03,0x01,0x01,
		0x03,0x03,0x07,0x0f,0x1f,0x3f,0x3b,0x33,0x07,0x07,0x06,0x00,0x00,0x00,0x00,0x00
	}, {
		0x00,0x00,0x00,0xe0,0xf0,0xf0,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
		0x80,0x80,0xf8,0xe8,0xc8,0xf0,0xe0,0xf0,0xc8,0xf0,0xe0,0xc0,0x80,0x00,0x00,0x00,
		0x00,0x00,0x00,0x03,0x07,0x0f,0x1f,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xef,0xcf,0x6f,0x6a,0x3f,0x1f,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x0f,0x1f,0x3f,0x3f,0x37,
		0x03,0x1f,0x3f,0x3f,0x1f,0x0f,0x1f,0x3f,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	} };

	current_frame = NEXT(current_frame);
	oled_write_raw_P(run[current_frame], LUNA_SIZE);
}


static void render_luna_bark(void) {
	static char const bark[LUNA_FRAMES][LUNA_SIZE] PROGMEM = { {
		0x00,0xc0,0xe0,0xf0,0xf0,0x30,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xc0,
		0xfc,0xf4,0xe4,0xf8,0x70,0xf8,0xe4,0xf8,0x70,0xc0,0x80,0x00,0x00,0x00,0x00,0x00,
		0x00,0x03,0x07,0x0f,0x1f,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xf7,0xf7,0x37,0x35,0x1f,0x0f,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x0f,0x1f,0x3f,0x3f,0x37,0x03,0x03,
		0x07,0x0f,0x1f,0x3f,0x3b,0x33,0x07,0x07,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	}, {
		0x00,0xe0,0xf0,0xf0,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xc0,
		0xc0,0xec,0xf4,0xe4,0xf8,0x70,0xf8,0xe4,0xf8,0x70,0xc0,0x80,0x00,0x00,0x00,0x00,
		0x00,0x03,0x07,0x0f,0x1f,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x77,0x37,0x35,0x1f,0x0f,0x20,0x4a,0x09,0x10,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x0f,0x1f,0x3f,0x3f,0x37,0x03,0x03,
		0x07,0x0f,0x1f,0x3f,0x3b,0x33,0x07,0x07,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	} };

	current_frame = NEXT(current_frame);
	oled_write_raw_P(bark[current_frame], LUNA_SIZE);
}


static void render_luna_sneak(void) {
	static char const sneak[LUNA_FRAMES][LUNA_SIZE] PROGMEM = { {
		0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xc0,0xc0,0xc0,0x80,0x00,0x00,0x00,0x00,
		0x00,0x00,0xc0,0x40,0x40,0x80,0x00,0x80,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x1e,0x3f,0xff,0xfb,0xfd,0xfd,0xfd,0xfd,0xfd,0xfc,0xfc,0xfc,
		0xfc,0xfe,0xff,0xff,0xfe,0xff,0xf7,0xff,0x7e,0x7f,0x57,0xfc,0xf8,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1f,0x3f,0x3f,0x3f,0x0f,0x1f,0x1f,0x03,0x07,
		0x1f,0x3f,0x3f,0x3f,0x0f,0x1f,0x1f,0x07,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x00
	}, {
		0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xc0,0xc0,0x80,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0xe0,0xa0,0x20,0xc0,0x80,0xc0,0x20,0xc0,0x80,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x3e,0x7f,0xf7,0xfb,0xfd,0xfd,0xfd,0xfd,0xfc,0xfc,0xfc,0xfc,
		0xfc,0xfe,0xff,0xff,0xff,0xff,0xfb,0xff,0xbf,0xbf,0xab,0xfe,0x7c,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x3f,0x0f,0x03,0x07,0x0f,0x1f,0x1f,0x07,
		0x1f,0x1f,0x0f,0x1f,0x3f,0x3f,0x37,0x07,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00
	} };

	current_frame = NEXT(current_frame);
	oled_write_raw_P(sneak[current_frame], LUNA_SIZE);
}


void render_luna_status(void) {
	// Animation timer
	static uint16_t anim_timer = 0;

#ifdef WPM_ENABLE
	static uint8_t prev_wpm = 0;
	static uint32_t tap_timer = 0;
	// tap_timer updated by sustained WPM
	if (get_current_wpm() > prev_wpm || get_mods()) { tap_timer = timer_read32(); }
	prev_wpm = get_current_wpm();
#else
	// tap_timer updated by key presses in process_record_user()
	extern uint32_t tap_timer;
#endif

	// Time gap between tap_timer updates
	uint32_t keystroke = timer_elapsed32(tap_timer);

	void animate_luna(void) {
		bool const caps = host_keyboard_led_state().caps_lock;

		render_logo();
		oled_set_cursor(0,8);
		if (get_mods() & MOD_MASK_SHIFT || caps) { render_luna_bark(); }
		else if (get_mods() & MOD_MASK_CAG) { render_luna_sneak(); }
		else if (keystroke < LUNA_FRAME_DURATION*2) { render_luna_run(); }
		else if (keystroke < LUNA_FRAME_DURATION*8) { render_luna_walk(); }
		else { render_luna_sit(); }
	}

	if (keystroke > OLED_TIMEOUT) { oled_off(); }
	else if (timer_elapsed(anim_timer) > LUNA_FRAME_DURATION) {
		anim_timer = timer_read();
		animate_luna();
	}

  oled_set_cursor(0,12);
    /* wpm counter */
    uint8_t n = get_current_wpm();
    char    wpm_str[4];
    oled_set_cursor(1, 14);
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);

    oled_set_cursor(0, 15);
    oled_write(" wpm", false);

}

// Init and rendering calls
oled_rotation_t oled_init_user(oled_rotation_t const rotation) {
  return OLED_ROTATION_270;
}

void oled_task_user(void) {
  extern void render_mod_status(void);
  if (is_keyboard_master()) { render_keymap_status(); }
  else { render_luna_status(); }
}

#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case PLOVER:
      if (!record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_on(_PLOVER);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
    case CMD_TAB:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_code(KC_LGUI);
        }
        cmd_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      return false;
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_cmd_tab_active = false;
    }
  }
}
