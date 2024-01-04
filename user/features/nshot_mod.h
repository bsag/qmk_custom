#pragma once

#include QMK_KEYBOARD_H

// Represents the four states an n-shot key can be in (from users/callum)
typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_down_unused,
    os_down_used,
} oneshot_state;

typedef struct {
    uint16_t      trigger;          // Keycode to activate the n-shot mod
    uint8_t       modbit;           // Modbit allows for mod combos.
    uint8_t       max_count;        // one-shot, two-shot, ..., n-shot.
    bool          active_on_rolls;  // Behavior for A down, Mod down, A up = (active_on_rolls == true ? Mod-A : a)
    oneshot_state state;            // Direct from users/callum
    uint8_t       count;            // N-shot count state
    uint16_t      timer;            // N-shot timer for tracking use as held mod
    bool          had_keydown;      // keydown state for (active_on_rolls == false)
} nshot_state_t;

extern nshot_state_t nshot_states[];
extern uint8_t             NUM_NSHOT_STATES;

// Custom one-or-more-shot sticky mod key implementation that
// prevents extra mod activation when rolling out of the mod,
// is configurable to allow or prevent mod activation rolling into the mod,
// treats held-only mods like normal held modifiers after TAPPING_TERM ms,
// and persists across layers with cancel- and ignore-keys.
// Based on the implementation in /users/callum, available in qmk master.

// Oneshot implementation. Call this in process_records.
void process_nshot_state(uint16_t keycode, keyrecord_t *record);

// Keys that should cancel the n-shot mod if tapped
bool is_nshot_cancel_key(uint16_t keycode);

// Keys that should not count towards n-shot usage (e.g., layer toggles)
// If your n-shots are on a layer, be sure to include that layer's access
// key in your ignores.
bool is_nshot_ignored_key(uint16_t keycode);