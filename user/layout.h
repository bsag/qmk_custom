#pragma once
#include QMK_KEYBOARD_H

enum layers {
  ALPHA,  
  UTIL,
  NUM,  
  NUM2,  
  SYM,
  WINNAV,
  FUN,
  ALWAYS
};

// Tap Dance keycodes
enum td_keycodes {
  ALT_LP  // Our example key: `LALT` when held, `(` when tapped. Add additional
          // keycodes for each tapdance.
};

enum custom_keycodes {
  QUOTE = SAFE_RANGE,
  LEADER,
  LLOCK,
  CIRC,
  GRV,
  TILD,
  DELIM,  // on the NUM word layer

  LPAREN,
  RPAREN,

  // Smart caps lock and layers that turn off on certain keys
  CAPSWORD,
  MINS,
  NUMWORD,
  SYMWORD,
  SENTENCE,
  CAMEL,
  KEBAB,

  // Layer management
  CANCEL,  // Cancel SYMWORD and NUMWORD
  CLEAR,  // Clear all WORD, one-shots and reset to BASE
  MG_THE,
  MG_ION,
  MG_ON,
  MG_ENT,
  MG_UST,
  MG_MENT,
  MG_VER,
  M_SENTENCE,

  // N-Shot Mods
  OS_LSFT,  // OS Mods
  OS_LCTL,  // OS Mods
  OS_LALT,  // OS Mods
  OS_LGUI,  // OS Mods
  TS_LCTL,  // Two-shot ctrl

  // used below in the thumb
  NEXTSEN,

  // German special nonsense
  A_UML,
  O_UML,
  U_UML,
  SZ,

  ARROW_L,
  ARROW_R,
  QU,
  KC_SCH,

  COPY_PASTE,
  SP_MOD,  // oneshot modifier and tap, nav layer on hold. See 'NAV_MOD'
  SP_SFT,
  CPYPASTE,

  SW_APP,
  SW_WIN,
  MOUSE_TGL,
  SLASH,
  UNDER,
  ALFRED,

  // lates stuff
  QUOTE_BRACKET,
  KC_PH,
  KC_TH,

  // window management.
  WN_WEST,
  WN_EAST,
  WN_NORTH,
  WN_SOUTH,
  W_ROTATE,
  W_ROTATE2,

  BI_PH,

};


#define META_DEAD LT(UTIL, KC_LGUI)

#define NICE_QU LALT(KC_3)
// macOS shortcuts
#define Z_UND G(KC_Z)
#define Z_CUT G(KC_X)
#define Z_CPY G(KC_C)
#define Z_PST G(KC_V)
#define Z_RDO S(G(KC_Z))
#define Z_LOCK C(G(KC_Q))
#define Z_SLEEP S(C(KC_EJCT))
#define Z_SHUT C(A(G(KC_PWR)))
#define Z_SSHT G(S(KC_4))
#define Z_SRCD G(S(KC_5))
#define Z_VSML A(KC_LSFT)
#define Z_HASH A(KC_3)
#define Z_AT S(KC_2)
#define EURO S(A(KC_2))
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TAB_L G(S(KC_LBRC))
#define TAB_R G(S(KC_RBRC))
#define SPACE_L A(G(KC_LEFT))
#define SPACE_R A(G(KC_RGHT))

// special keys
#define MAGIC QK_ALT_REPEAT_KEY
#define REPEAT QK_REPEAT_KEY
#define REP_SFT LSFT_T(QK_REPEAT_KEY)
#define ENT_GUI LGUI_T(KC_ENTER)

#define ESC_SYM LT(SYM,KC_ESC)
#define COLON_SYM LT(SYM,KC_COLON)

#define M_LT LT(NUM, KC_LT)
#define M_GT LT(SYM, KC_GT)

// thumb keys!
#define NAV_SPC LT(UTIL, KC_SPC)
#define MEH_SPC MEH_T(KC_SPC)
#define NUM_QUO LT(NUM, KC_QUOT)
#define OS_SYM OSL(SYM)
#define OS_MEH OSM(MOD_MEH)
#define UM_CTL LCTL_T(KC_U)

#define ___A___ KC_A
#define ___B___ KC_B
#define ___C___ KC_C
#define ___D___ LSFT_T(KC_D)
#define ___E___ KC_E
#define ___F___ KC_F
#define ___G___ KC_G
#define ___H___ KC_H
#define ___I___ KC_I
#define ___J___ KC_J
#define ___K___ KC_K
#define ___L___ KC_L
#define ___M___ KC_M
#define ___N___ RSFT_T(KC_N)
#define ___O___ KC_O
#define ___P___ KC_P
#define ___Q___ KC_Q
#define ___R___ KC_R
#define ___S___ KC_S
#define ___T___ KC_T
#define ___U___ KC_U
#define ___V___ KC_V
#define ___W___ KC_W
#define ___X___ KC_X
#define ___Y___ KC_Y
#define ___Z___ KC_Z
#define _COMMA_ KC_COMM
#define __DOT__ KC_DOT
#define _SLASH_ KC_SLSH
#define _SQUOT_ KC_QUOT
#define _DQUOT_ KC_DQUO
#define _MINUS_ KC_MINS
#define __HASH_ KC_HASH
#define _SEMIC_ KC_SCLN
#define _QUEST_ KC_QUES

#define ___0___ KC_0
#define ___2___ KC_2
#define ___4___ KC_4
#define ___6___ KC_6
#define ___8___ KC_8

#define ___1___ KC_1
#define ___3___ KC_3
#define ___5___ KC_5
#define ___7___ KC_7
#define ___9___ KC_9

#define _______ KC_TRNS
#define _XXXXX_ KC_NO
#define ___________________________________________ \
  _______, _______, _______, _______, _______


// ----------------
// layout wrappers inspired by https://github.com/pixelbreaker/qmk_userspace

#define _STURDY \
  ___V___, ___M___, ___L___, ___C___, ___P___,      ___B___, MAGIC,   ___U___, ___O___, _SQUOT_, \
  ___S___, ___T___, ___R___, ___D___, ___Y___,      ___F___, ___N___, ___E___, ___A___, ___I___, \
  ___X___, ___K___, ___J___, ___G___, ___W___,      ___Z___, ___H___, _COMMA_, __DOT__, KC_QUES, \
                    LT(UTIL,KC_TAB), NAV_SPC, REP_SFT,      ENT_GUI,  LT(NUM,KC_BSPC),  LT(FUN,KC_DEL)

/*
  b l d w z        ' f o u j 
  n r t s g        y h a e i
  q x m c v        k p , . /
*/
#define _GRAPHITE \
  ___B___, ___L___, ___D___, ___W___, ___Z___,      _SQUOT_, ___F___, ___O___, ___U___, ___J___, \
  ___N___, ___R___, ___T___, ___S___, ___G___,      ___Y___, ___H___, ___A___, ___E___, ___I___, \
  ___Q___, ___X___, ___M___, ___C___, ___V___,      ___K___, ___P___, _COMMA_, __DOT__, KC_QUES, \
                    KC_F18, MAGIC_GUI, KC_LGUI,     UM_CTL, NAV_SPC,  KC_F19

/*
  x c l f ~   ~ y o u '
  r s n t p   k h e i a
  ~ w m g b   j d , . ~
*/
#define _BIRD \
  ___X___, ___C___, ___L___, ___F___, ___V___,      ___Z___, ___Y___, ___O___, ___U___, _SQUOT_, \
  ___R___, ___S___, ___N___, ___T___, ___P___,      ___K___, ___H___, ___E___, ___I___, ___A___, \
  ___Q___, ___W___, ___M___, ___G___, ___B___,      ___J___, ___D___, _COMMA_, __DOT__, _SLASH_, \
                    KC_F18, MAGIC_GUI, KC_LGUI,     UM_CTL, NAV_SPC,  KC_F19


#define _BASE \
  ___V___, ___W___, ___F___, ___P___, ___K___,      ___J___, ___L___, ___U___, ___Y___, _SQUOT_, \
  ___A___, ___R___, ___S___, ___T___, ___G___,      ___M___, ___N___, ___E___, ___I___, ___O___, \
  _XXXXX_, ___X___, ___C___, ___D___, _XXXXX_,      _XXXXX_, ___H___, _COMMA_ , __DOT__ , _XXXXX_, \
                    NUM_QUO, NAV_SPC, SPACE_L,      KC_BSLS, OS_LSFT,  NUMWORD

#define _RECURVA \
  ___F___, ___R___, ___D___, ___P___, ___V___,      ___Q___, ___M___, ___U___, ___O___, ___Y___, \
  ___S___, ___N___, ___T___, ___C___, ___B___,      __DOT__, ___H___, ___E___, ___A___, ___I___, \
  ___Z___, ___J___, ___K___, ___G___, ___W___,      ___X___, ___L___, KC_SCLN, _SQUOT_ , _COMMA_, \
                LT(KC_TAB,UTIL), NAV_SPC, OS_LSFT,   ESC_SYM, LT(NUM,KC_BSPC),  NUMWORD

/*
  B   Y   O   U           L   D   W   V    Z
  C   I   E   A           H   T   S   N    Q
  G   X   J   K           R   M   F   P

*/
#define _ENGRAM \
  ___B___, ___Y___, ___O___, ___U___, _SQUOT_,      _DQUOT_, ___L___, ___D___, ___W___, ___V___, \
  ___C___, ___I___, ___E___, ___A___, _COMMA_,      __DOT__, ___H___, ___T___, ___S___, ___N___, \
  ___G___, ___X___, ___J___, ___K___, ___Z___,      ___Q___, ___R___, ___M___, ___F___, ___P___, \
                LT(KC_TAB,UTIL), NAV_SPC, OS_LSFT,   ESC_SYM, LT(NUM,KC_BSPC),  NUMWORD



/*
     ╭─────────────────────╮ ╭──────────────────────╮
ESC  │  X   W   M   G  "[  │ │  #$  .:  ']   J   B  │ BSP
TAB  │  S   C   N   T   K  | |  ,;   A   E   I   H  │ Tg(Num)
LSFT │  V   P   L   D  / * │ │  -+   U   O   Y   F  │ RSFT
     ╰──────╮  App BSP  R  │ │  SPC RET TAB  ╭──────╯
            ╰──────────────╯ ╰───────────────╯
*/
#define _HANDS_DOWN_VV \
  ___X___, ___W___, ___M___, ___G___, _DQUOT_,      KC_HASH, __DOT__, _SQUOT_, ___J___, ___B___, \
  ___S___, ___C___, ___N___, ___T___, ___K___,      _COMMA_, ___A___, ___E___, ___I___, ___H___, \
  ___V___, ___P___, ___L___, ___D___, KC_SLSH,      KC_MINS, ___U___, ___O___, ___Y___, ___F___, \
                    SPACE_L, ___R___, KC_MEH,       UM_CTL,  NAV_SPC,  LT(NUM,KC_TAB)

#define _SNTH \
  ___X___, ___P___, ___D___, ___M___, ___Q___,      KC_EQL,  ___Y___, ___O___, ___U___, _COMMA_, \
  ___S___, ___N___, ___T___, ___H___, ___V___,      ___G___, ___C___, ___A___, ___E___, ___I___, \
  ___F___, ___B___, ___K___, ___L___, ___J___,      ___Z___, ___W___, _DQUOT_, KC_SLSH, __DOT__, \
                    SPACE_L, ___R___, KC_MEH,       UM_CTL,  NAV_SPC,  LT(NUM,KC_TAB)


#define _UTIL \
  SW_APP,  TAB_L,   TAB_R,   SW_WIN,  KC_NO,               KC_NO, KC_BSPC, KC_UP,   KC_DEL,  KC_NO, \
  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, OSM(MOD_MEH),        FWD,   KC_LEFT, KC_DOWN, KC_RGHT, BACK, \
  Z_UND,   Z_CUT,   Z_CPY,   Z_PST,   ALFRED,              KC_NO, KC_ESC,  KC_COLON,KC_NO,   KC_NO, \
                    KC_SPC, KC_SPC,   KC_F19            , _______, _XXXXX_, _______

#define _NUM \
  KC_TILD ,KC_PLUS ,KC_PAST, KC_EXLM, _______      ,_______, KC_HASH,  KC_AT,   KC_CIRC, _COMMA_, \
  ___7___ ,___5___ ,___3___ ,___1___, KC_BSLS      ,___0___, ___0___,  ___2___, ___4___, ___6___ , \
  _______ ,KC_LT   ,KC_GT,   ___9___, _______      ,KC_SLSH, ___8___,  KC_LPRN, KC_RPRN, __DOT__, \
                    _______, _______, _______      ,_______, _______, _______

#define _NUM2 \
  KC_SLSH ,___7___, KC_LALT, KC_LCTL, KC_PLUS      ,_______, ___1___, ___2___, ___3___, _COMMA_, \
  ___0___, _XXXXX_, KC_LGUI, KC_LSFT, OSM(MOD_MEH)      ,_______, ___4___, ___5___, ___6___, _______ , \
  KC_PAST ,___4___, ___5___, ___6___, KC_EQL       ,KC_SLSH, ___7___, ___8___, ___9___, __DOT__, \
                    _______, KC_SPC,  _______      ,_______, ___0___, _______

#define _ALWAYS_ACC \
  _______ ,KC_ESC, KC_COLON, _______, _______      ,_______, _______,  _______, _______, _______, \
  _______, KC_PERC,_SLASH_, KC_ENTER, _______      ,_______, _______,  _______, _______, _______ , \
  _______ ,_______, _______, S(KC_1), _______      ,_______, _______,  _______, _______, QK_BOOT, \
                    _______, _______, _______      ,_______, _______, _______

/*
#define _SYM \
  KC_TILD ,KC_PLUS ,KC_PAST, KC_EXLM, _______      ,_______, KC_HASH,  KC_AT,   KC_CIRC, _COMMA_, \
  KC_PIPE ,KC_LCBR ,KC_RCBR ,KC_MINS, KC_BSLS      ,KC_GRV,  KC_QUES,  KC_LBRC, KC_RBRC, KC_DLR , \
  KC_UNDS ,KC_LT   ,KC_GT,   KC_PERC, _______      ,KC_SLSH, KC_AMPR,  KC_LPRN, KC_RPRN, __DOT__, \
                    _______, _______, _______      ,_______, _______, _______
*/
#define _SYM \
  KC_GRV  ,KC_LT   ,KC_GT,   KC_AT  , KC_DOT       ,KC_AMPR, MAGIC,    KC_LBRC, KC_RBRC, _______, \
  KC_EXLM ,KC_MINS ,KC_PLUS ,KC_EQL,  KC_HASH      ,KC_PIPE, KC_COLON, KC_LPRN, KC_RPRN, KC_PERC , \
  _______ ,KC_SLSH ,KC_PAST, KC_CIRC, _______      ,KC_TILD, KC_AMPR,  KC_LCBR, KC_RCBR, _______, \
                    _______, _______, _______      ,_______, _______, _______

#define _WINNAV \
  KC_NO,        W_ROTATE,     WN_NORTH,     W_ROTATE2,    KC_PLUS,      KC_BSLS, MEH(KC_6),    MEH(KC_7),      MEH(KC_8),     KC_TILD, \
  SPACE_L,      WN_WEST,      A(KC_F),      WN_EAST,      SPACE_R,      KC_NO,   MEH(KC_4),    MEH(KC_5),      MEH(KC_6),     LALT_T(KC_6), \
  KC_NO,        KC_NO,        WN_SOUTH,     KC_NO,        KC_NO,        KC_NO,   MEH(KC_1),    MEH(KC_2),      MEH(KC_3),     KC_SLSH, \
                              NAV_SPC,      KC_1,         KC_2,         KC_2,  KC_1,   MAGIC_GUI

#define _FUN \
  KC_NO,        W_ROTATE,     WN_NORTH,     W_ROTATE2,    KC_PLUS,           KC_BSLS, KC_F7,        KC_F8,           KC_F9,      KC_F10, \
  OS_LALT,      OS_LCTL,      OS_LGUI,      OS_LSFT,      OSM(MOD_MEH),      KC_NO,   KC_F4,        KC_F5,           KC_F6,      KC_F11, \
  KC_NO,        KC_NO,        WN_SOUTH,     KC_NO,        KC_NO,             KC_NO,   KC_F1,        KC_F2,           KC_F3,      KC_F12, \
                              KC_NO,        KC_NO,        KC_NO,             KC_2,    KC_1,         MAGIC_GUI


// Layout aliases for json keymap
#define LAYOUT_redox(...) LAYOUT(__VA_ARGS__)

#define CONV_REDOX( \
  k15, k16, k17, k18, k19,        k22, k23, k24, k25, k26, \
  k29, k30, k31, k32, k33,        k36, k37, k38, k39, k40, \
  k43, k44, k45, k46, k47,        k50, k51, k52, k53, k54, \
            k59, k60, k61,        k64, k65, k66 \
) \
     KC_NO   ,KC_7    ,KC_5    ,KC_3    ,KC_1    ,KC_9    ,                                            KC_8    ,KC_0    ,KC_2    ,KC_4    ,KC_6  ,KC_NO   , \
     KC_TAB  ,k15     ,k16     ,k17     ,k18     ,k19     ,KC_F11   ,                         KC_F12  ,k22     ,k23     ,k24     ,k25     ,k26     ,KC_BSLS , \
     k15     ,k29     ,k30     ,k31     ,k32     ,k33     ,KC_DLR  ,                         KC_DLR   ,k36     ,k37     ,k38     ,k39     ,k40 ,    k26 , \
     KC_LSFT ,k43     ,k44     ,k45     ,k46     ,k47     ,KC_NO   ,QK_BOOT ,        QK_BOOT ,KC_NO   ,k50     ,k51     ,k52     ,k53     ,k54     ,KC_RSFT , \
     KC_LCTL ,KC_LALT ,KC_LEFT ,KC_RIGHT   ,     k59     ,    k60     ,k61     ,        k64      ,k65     ,k66     ,KC_LBRC ,KC_RBRC ,KC_NO   ,KC_NO 

#define REDOX(k) CONV_REDOX(k)

#define LAYOUT_TOTEM(...) LAYOUT(__VA_ARGS__)
#define TOTEM(k) CONV_TOTEM(k)
#define CONV_TOTEM( \
  k15, k16, k17, k18, k19,        k22, k23, k24, k25, k26, \
  k29, k30, k31, k32, k33,        k36, k37, k38, k39, k40, \
  k43, k44, k45, k46, k47,        k50, k51, k52, k53, k54, \
            k59, k60, k61,        k64, k65, k66 \
) \
        k15, k16, k17, k18, k19,        k22, k23, k24, k25, k26, \
        k29, k30, k31, k32, k33,        k36, k37, k38, k39, k40, \
KC_NO,  k43, k44, k45, k46, k47,        k50, k51, k52, k53, k54, KC_NO, \
                  k59, k60, k61,        k64, k65, k66


// -------------------------------------------------------------------------------------------------------- //

#define LAYOUT_FERRIS(...) LAYOUT(__VA_ARGS__)

#define FERRIS(k) CONV_FERRIS(k)

#define CONV_FERRIS( \
  k15, k16, k17, k18, k19,        k22, k23, k24, k25, k26, \
  k29, k30, k31, k32, k33,        k36, k37, k38, k39, k40, \
  k43, k44, k45, k46, k47,        k50, k51, k52, k53, k54, \
            k59, k60, k61,        k64, k65, k66 \
) \
        k15, k16, k17, k18, k19,        k22, k23, k24, k25, k26, \
        k29, k30, k31, k32, k33,        k36, k37, k38, k39, k40, \
        k43, k44, k45, k46, k47,        k50, k51, k52, k53, k54, \
                      k60, k61,         k64, k65


#define LAYOUT_PLANCK(...) LAYOUT(__VA_ARGS__)
#define PLANCK(k) CONV_PLANCK(k)
#define CONV_PLANCK( \
    k01, k02, k03, k04, k05,    k06, k07, k08, k09, k0a, \
    k11, k12, k13, k14, k15,    k16, k17, k18, k19, k1a, \
    k21, k22, k23, k24, k25,    k26, k27, k28, k29, k2a, \
              k33, k34, k35,    k36, k37, k38            \
    ) \
     KC_ESC, k01, k02, k03, k04, k05, \
     KC_TAB, k11, k12, k13, k14, k15, \
     OS_LSFT, k21, k22, k23, k24, k25, \
     KC_LCTL, KC_LALT, KC_LGUI, KC_LALT, KC_RCTL, k36, \
     k06, k07, k08, k09, k0a, KC_BSPC, \
     k16, k17, k18, k19, k1a, KC_ENTER, \
     k26, k27, k28, k29, k2a, OSL(NUM), \
     k37, OSL(NUM), KC_RGUI, OSL(NUM), k34, k35



/*

#define _TEMPLATE_LAYER \
  _______ ,_______, _______, _______, _______      ,_______, _______,  _______, _______, _______, \
  _______, _______, _______, _______, _______      ,_______, _______,  _______, _______, _______ , \
  _______ ,_______, _______, _______, _______      ,_______, _______,  _______, _______, _______, \
                    _______, _______, _______      ,_______, _______, _______

*/