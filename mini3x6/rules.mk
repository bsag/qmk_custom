SPLIT_KEYBOARD		= yes
STENO_ENABLE		= no
SERIAL_ENABLE		= yes
NKRO_ENABLE			= no
EXTRAKEY_ENABLE		= yes
MIDI_ENABLE			= no
AUDIO_ENABLE		= no
MOUSEKEY_ENABLE     = no     # Mouse keys
RGBLIGHT_ENABLE     = no    # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE   = no
VIA_ENABLE          = no         # Enable VIA
OLED_DRIVER_ENABLE  = yes
LTO_ENABLE          = yes
WPM_ENABLE			= yes
COMBO_ENABLE 		= yes
AUTO_SHIFT_ENABLE   = yes
SRC += caps_word.c
SRC += oneshot.c
SRC += swapper.c