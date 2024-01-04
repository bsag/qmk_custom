#include "nshot_mod.h"
#include "layout.h"

#define modbit_lclg (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI))

// for all mods, the last key of the n-shot will always behave as such:
// [Mod down, mod up, previous n-shot keys if extant], A down, B down, A up, B up: Mod-A b
// For key progression A down, Mod down, A up, Mod up:
nshot_state_t  nshot_states[] = {
    {OS_LSFT, MOD_BIT(KC_LSFT), 1, true,  os_up_unqueued, 0, 0, false}, // S-a
    {OS_LCTL, MOD_BIT(KC_LCTL), 1, true,  os_up_unqueued, 0, 0, false}, // C-a
    {OS_LALT, MOD_BIT(KC_LALT), 1, true,  os_up_unqueued, 0, 0, false}, // A-a
    {OS_LGUI, MOD_BIT(KC_LGUI), 1, true,  os_up_unqueued, 0, 0, false}, // G-a
    //{OS_LGLC, modbit_lclg,      1, true,  os_up_unqueued, 0, 0, false}, // G-C-a
    //{TS_LCTL, MOD_BIT(KC_LCTL), 2, true,  os_up_unqueued, 0, 0, false}, // C-a
    //{OSR_SFT, MOD_BIT(KC_LSFT), 1, false, os_up_unqueued, 0, 0, false}  // a
};
uint8_t        NUM_NSHOT_STATES = sizeof(nshot_states) / sizeof(nshot_state_t);

void process_nshot_state(uint16_t keycode, keyrecord_t *record) {
    nshot_state_t *curr_state = NULL;

    for (int i = 0; i < NUM_NSHOT_STATES; ++i) {
        curr_state = &nshot_states[i];
        uint8_t max_count = curr_state->max_count * 2;

        if (keycode == curr_state->trigger) {
            if (record->event.pressed) {
                // Trigger keydown
                if (curr_state->state == os_up_unqueued) {
                    register_mods(curr_state->modbit);
                }
                curr_state->state = os_down_unused;
                curr_state->count = 0;
                curr_state->had_keydown = curr_state->active_on_rolls;
                curr_state->timer = timer_read();
            } else {
                // Trigger keyup
                switch (curr_state->state) {
                    case os_down_unused:
                        // If we didn't use the mod while trigger was held, queue it.
                        if((timer_elapsed(curr_state->timer)) < TAPPING_TERM) {
                        curr_state->state = os_up_queued;
                        break;
                        }
                        curr_state->state = os_up_unqueued;
                            unregister_mods(curr_state->modbit);
                            break;
                    case os_down_used:
                        // If we did use the mod while trigger was held, unregister it.
                        curr_state->state = os_up_unqueued;
                        unregister_mods(curr_state->modbit);
                        break;
                    default:
                        break;
                }
            }
        } else {
            if (record->event.pressed) {
                if (is_nshot_cancel_key(keycode) && curr_state->state != os_up_unqueued) {
                    // Cancel oneshot on designated cancel keydown.
                    curr_state->state = os_up_unqueued;
                    curr_state->count = 0;
                    curr_state->had_keydown = curr_state->active_on_rolls;
                    unregister_mods(curr_state->modbit);
                }

                // Check for oneshot completion on sequential keys while rolling.
                // curr_state->state will only be os_up_queued after the n-shot has been triggered.
                if (curr_state->state == os_up_queued && !is_nshot_ignored_key(keycode)) {
                    // Increment on sequential key press.
                    curr_state->count = curr_state->count + 1;
                    curr_state->had_keydown = true;

                    // If count > max_count, the previous key hit maxed out the n-shot.
                    // Complete the n-shot; this current keycode will be pressed sans mod.
                    if (curr_state->count == max_count) {
                        curr_state->state = os_up_unqueued;
                        curr_state->count = 0;
                        curr_state->had_keydown = curr_state->active_on_rolls;
                        unregister_mods(curr_state->modbit);
                    }
                }

                if (curr_state->state == os_down_unused){
                    curr_state->had_keydown = true;
                }
            } else {
                if (!is_nshot_ignored_key(keycode)) {
                    // On non-ignored keyup, consider the oneshot used.
                    switch (curr_state->state) {
                        case os_down_unused:
                            // if there's been a keydown, the mod is being used normally. Mark as used.
                            if(curr_state->had_keydown){
                                curr_state->state = os_down_used;
                            }
                            // if there has *not* been a keydown, the mod is being rolled into
                            // and this first keyup is not part of the mod behavior.
                            break;
                        case os_up_queued:
                            // If there's been a keydown, the mod key is being used as an n-shot.
                            // Increment the keycount.
                            if (curr_state->had_keydown){
                                curr_state->count = curr_state->count + 1;
                            }

                            // If the n-shot max has been reached, complete the n-shot.
                            if (curr_state->count == max_count) {
                                curr_state->state = os_up_unqueued;
                                curr_state->count = 0;
                                curr_state->had_keydown = curr_state->active_on_rolls;
                                unregister_mods(curr_state->modbit);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

bool is_nshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case CLEAR:
        case CANCEL:
        case NAV_SPC:
            if (layer_state_is(UTIL)) {
                return true;
            } else {
                return false;
            }            
        default:
            return false;
    }
}

bool is_nshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        //case NAVMODE:
        case NAV_SPC:
        case NUMWORD:
        case OS_LSFT:
        case OS_LCTL:
        case OS_LALT:
        case OS_LGUI:
            return true;
        default:
            return false;
    }
}