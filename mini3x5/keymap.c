#include QMK_KEYBOARD_H

// Callum oneshot mods and swapper
// https://github.com/callum-oakley/qmk_firmware/blob/master/users/callum
#include "caps_word.h"
#include "swapper.h"
#include "keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Colemak Mod-DH layout
  [_CDH] = LAYOUT_split_3x5_2(
                              KC_Q, KC_W, KC_F, KC_P, KC_B,                KC_J, KC_L, KC_U,    KC_Y,   KC_QUOT,
                              QHOME_A, QHOME_R, QHOME_S, QHOME_T, KC_G,    KC_M, QHOME_N, QHOME_E, QHOME_I, QHOME_O,
                              KC_Z, KC_X, KC_C, KC_D, KC_V,                KC_K, KC_H, KC_COMM, KC_DOT, KC_SCLN,
                                                 NUM, NAV_BSPC,        KC_SPC, FUN
                              ),

  // PHD = Platinum Hands Down layout
   [_PHD] = LAYOUT_split_3x5_2(
                              KC_J,    KC_G,    KC_H,    KC_P,    KC_V,      KC_MINS, KC_DOT,  KC_COMM, KC_QUOT, KC_DQUO,
                              HHOME_R, HHOME_S, HHOME_N, HHOME_T, KC_B,      KC_SLSH, HHOME_A, HHOME_E, HHOME_C, HHOME_I,
                              KC_X,    KC_F,    KC_M,    KC_D,    KC_K,      KC_BSPC, KC_U,    KC_O,    KC_W,    KC_Y,
                                                         NUM,   NAV_L,       KC_SPC, FUN
                              ),

  [_NUM] = LAYOUT_split_3x5_2(
                              KC_NO,   PMIN,   S(KC_EQL),  KC_MINS, GBPD,   KC_GRV,  KC_7, KC_8, KC_9, KC_0,
                              KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,    KC_LBRC,  KC_4, KC_5, KC_6, KC_RBRC,
                              KC_NO,   KC_NO,   KC_EQL,  S(KC_MINS), KC_NO,    KC_BSLS, KC_1, KC_2, KC_3, KC_SLSH,
                                                     KC_TRNS,    KC_TRNS,   KC_SPC,  KC_TRNS
                              ),

  [_NAV] = LAYOUT_split_3x5_2(
                              SW_APP,  KC_NO,   TAB_L,  TAB_R,  KC_TAB,      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_BSPC,
                              KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, M_SAVE,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
                              M_UNDO,  M_CUT,   M_COPY, M_DUP,   M_PSTE,     WS_L,    LAU,     KC_NO,   WS_R,    KC_DEL,
                                                         KC_TRNS, KC_TRNS,   KC_SPC, KC_TRNS
                              ),

  [_FUN] = LAYOUT_split_3x5_2(
                              RESET,   KC_VOLD,  KC_MUTE,  KC_VOLU,   KC_CAPS,     KC_F12,  KC_F7, KC_F8, KC_F9, KC_NO,
                              KC_LCTL, KC_LALT,  KC_LGUI,  KC_LSFT,   KC_NO,       KC_F11,  KC_F4, KC_F5, KC_F6, KC_NO,
                              TG_PHD,  KC_MPRV,  KC_MPLY,  KC_MNXT,   KC_NO,       KC_F10,  KC_F1, KC_F2, KC_F3, KC_NO,
                                                           KC_TRNS,  KC_TRNS,      KC_SPC, KC_TRNS
                              )
};

bool sw_app_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_caps_word(keycode, record)) { return false; }

  update_swapper(
                 &sw_app_active, KC_LGUI, KC_TAB, SW_APP,
                 keycode, record
                 );

  return true;
}

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     return update_tri_layer_state(state, _LMOD, _RMOD, _NUM); */
/* } */
