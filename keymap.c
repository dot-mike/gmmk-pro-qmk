#include QMK_KEYBOARD_H

// Tap Dance declarations
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    TD_HOME_DANCE,
    TD_PRTSCRN_INS,
};

// For the x tap dance. Put it here so it can be used in any keymap
void td_homedance_finished(qk_tap_dance_state_t *state, void *user_data);
void td_homedance_reset(qk_tap_dance_state_t *state, void *user_data);

td_state_t cur_dance(qk_tap_dance_state_t *state);

// Tap Dance declerations end

// Layers
#define _BASE 0
#define _FN 1

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.

    /*
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    |        |        |        |        |        |        |        |        |        |        |        |        |                 |        |        |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+        +--------+
    //    |                 |        |        |        |        |        |        |        |        |        |        |                 +--------+        |
    //    +-----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+        +--------+
    //    +--------+--------+--------+--------------------------------------------------------------+--------+--------+--------+--------+--------+--------+
    //    |        |        |        |                                                              |        |        |        |        |        |        |
    //    +--------+--------+--------+--------------------------------------------------------------+--------+--------+--------+--------+--------+--------+

    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    */

    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    | Esc    | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | PrtScr |        | Mute   |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    | |§     | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | +      | \      | BackSp |        | Home   |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    | Tab    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | Å      | ¨     | \       |        | PgUp   |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    | Caps   | A      | S      | D      | F      | G      | H      | J      | K      | L      | Ø      | Æ      | Enter           |        | PgDn   |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+        +--------+
    //    | Shift           | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | -      | Shift           +--------+ End    |
    //    +-----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+ Up     +--------+
    //    +--------+--------+--------+--------------------------------------------------------------+--------+--------+--------+--------+--------+--------+
    //    | Ctrl   | Alt    | Super  |                            Space                             | Alt    | MO(1)  | Ctrl   | Left   | Down   | Right  |
    //    +--------+--------+--------+--------------------------------------------------------------+--------+--------+--------+--------+--------+--------+

    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TD(TD_PRTSCRN_INS), KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            TD(TD_HOME_DANCE),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                     KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,             KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,           KC_UP,    KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    | Reset  | R_RMOD | R_MOD  | R_CALC | MSEL   | R_VAD  | R_VAI  | MPRV   | MPLY   | MNEXT  | MUTE   | VOLD   | VOLU   | Insert |        |        |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    |        | R_TOG  |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+        +--------+
    //    |        |        |        |        |        |        |        |        |        |        | -      |        |                 |        |        |
    //    +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+        +--------+
    //    |                 | R_HUD  | R_HUI  | R_SAD  | R_SAI  |        | NK_TOG |        |        |        |        |                 +--------+        |
    //    +-----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+ R_SPI  +--------+
    //    +--------+--------+--------+--------------------------------------------------------------+--------+--------+--------+--------+--------+--------+
    //    |        |        |        |                                                              |        |        |        |        | R_SPD  |        |
    //    +--------+--------+--------+--------------------------------------------------------------+--------+--------+--------+--------+--------+--------+
    [_FN] = LAYOUT(
        RESET,   RGB_RMOD, RGB_MOD, KC_CALC, KC_MSEL, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_INS,           _______,
        _______, RGB_TOG,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______,  RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_SPI, _______,
        _______, _______,  _______,                            _______,                            _______, _______, _______, _______, RGB_SPD, _______
    ),

};
// clang-format on

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {.is_press_action = true, .state = TD_NONE};

void td_homedance_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_HOME);
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_TAP:
            register_code(KC_DELETE);
            break;
        default:
            break;
    }
}

void td_homedance_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_HOME);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_TAP:
            unregister_code(KC_DELETE);
            break;
        default:
            break;
    }
    xtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_HOME_DANCE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_homedance_finished, td_homedance_reset),
    [TD_PRTSCRN_INS] = ACTION_TAP_DANCE_DOUBLE(KC_PSCR, KC_INS),
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return false;
}
#endif // ENCODER_ENABLE



void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color_all(RGB_WHITE);
    }
}
