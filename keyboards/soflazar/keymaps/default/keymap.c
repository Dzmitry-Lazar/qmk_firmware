/* Copyright 2023 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "quantum.h"

#include "ws2812.h" // Or the appropriate header for your LED type

#include <stdio.h>

#include QMK_KEYBOARD_H

enum sofle_layers { _DEFAULTS = 0, _QWERTY = 0, _LOWER, _RAISE, _QUOTES };

enum custom_keycodes { KC_QWERTY = SAFE_RANGE, KC_LOWER, KC_RAISE, KC_ADJUST, KC_D_MUTE, KC_ALTF7 };

enum { TD_LCBR, TD_F7, TD_BSPC, TD_PRN, TD_ABK, TD_UNDS };
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LCBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR), [TD_F7] = ACTION_TAP_DANCE_DOUBLE(KC_F7, LALT(KC_F7)), [TD_BSPC] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, KC_DEL), [TD_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN), [TD_ABK] = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK), [TD_UNDS] = ACTION_TAP_DANCE_DOUBLE(KC_UNDS, KC_MINS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LCTL | LGUI | LCMD | LALT | /Enter  /       \Space \  | RALT | RCMD | RGUI | RCTL |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */

    /*
       _______,  _______,  _______,  _______,  _______,  _______,                                               _______,  _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  _______,  _______,  _______,                                               _______,  _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  _______,  _______,  _______,                                               _______,  _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
   */

    [_QWERTY] = LAYOUT(QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQUAL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TD(TD_BSPC), KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER, KC_HOME, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, RSFT_T(KC_DOT), KC_UP, KC_END, KC_LCTL, KC_LGUI, KC_LALT, KC_RAISE, KC_ENTER, KC_SPC, KC_LOWER, LT(_QUOTES, KC_LBRC), KC_RBRC, LT(_RAISE, KC_SLSH), KC_SPC, KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_RIGHT),

    [_LOWER] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, _______, _______, _______, _______, _______, KC_MINS, TD(TD_F7), KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______, _______, _______, KC_BSPC, _______, _______, KC_HOME, KC_UP, KC_END, KC_BSPC, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL, KC_MUTE, _______, _______, _______, _______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO, _______, KC_BSLS, _______, _______, _______, _______, KC_PGDN, _______),

    [_RAISE] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, _______, _______, _______, _______, _______, KC_MINS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______, _______, _______, KC_BSPC, _______, _______, KC_MS_WH_DOWN, KC_MS_UP, KC_MS_WH_UP, KC_BSPC, _______, _______, _______, _______, _______, _______, _______, KC_MS_BTN2, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_BTN1, KC_MUTE, _______, _______, _______, _______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO, _______, KC_BSLS, _______, _______, _______, _______, KC_PGDN, _______),

    [_QUOTES] = LAYOUT(UG_NEXT, UG_HUEU, UG_SATU, UG_VALU, UG_SPDU, _______, _______, _______, _______, _______, _______, _______, UG_TOGG, _______, _______, _______, TD(TD_UNDS), TD(TD_PRN), _______, _______, _______, _______, _______, _______, CG_TOGG, _______, _______, _______, KC_SCLN, TD(TD_LCBR), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_EQUAL, TD(TD_ABK), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV)},
    [1] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV)},
    [2] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV)},
    [3] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV)},
};

uint32_t    anim_sleep = 0;
static void render_falling_symbols(void) {
    static const char PROGMEM symbols[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static uint8_t            positions[128];
    static uint8_t            speeds[128];
    static uint8_t            initialized = 0;

    if (!initialized) {
        for (uint8_t i = 0; i < 128; i++) {
            positions[i] = rand() % 32;
            speeds[i]    = (rand() % 3) + 1;
        }
        initialized = 1;
    }

    uint8_t wpm = get_current_wpm();

    if (timer_elapsed32(anim_sleep) < 200 - wpm) {
        return;
    }

    anim_sleep = timer_read32();

    uint8_t speed_factor = wpm / 10; // Adjust this factor as needed

    oled_clear();

    for (uint8_t i = 0; i < 128; i++) {
        uint8_t pos    = positions[i];
        uint8_t speed  = speeds[i] + speed_factor;
        char    symbol = pgm_read_byte(&symbols[rand() % (sizeof(symbols) - 1)]);

        oled_set_cursor(i, pos);
        oled_write_char(symbol, false);

        positions[i] = (pos + speed) % 32;
    }
    oled_render_dirty(true);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // if (!is_keyboard_master()) {
    return OLED_ROTATION_270; // flips the display 180 degrees if offhand
    //}

    return rotation;
}

static void print_status_narrow(void) {
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _QUOTES:
            oled_write_P(PSTR("Quote\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

static uint16_t off_timer;
static bool     isOff = false;

uint32_t anim_idle_timer = 0;

static const char PROGMEM sleep_frames[][3] = {"Z  ", " Z ", "  Z"};
static uint16_t           anim_timer        = 0;
static uint8_t            current_frame     = 0;
static void               z_anim(void) {
    if (timer_elapsed(anim_timer) > 200) { // Change frame every 200ms
        anim_timer    = timer_read();
        current_frame = (current_frame + 1) % 3; // Cycle through frames
    }

    // Clear the OLED screen
    oled_clear();

    // Display the current frame
    oled_write_P(sleep_frames[current_frame], false);
}
bool oled_task_user(void) {
    char wpm = get_current_wpm();

    if (wpm == 000) {
        if (timer_elapsed32(anim_idle_timer) > OLED_TIMEOUT) {
            oled_off(); // not essential but turns on animation OLED with any alpha keypress
            return false;
        }
    } else {
        anim_idle_timer = timer_read32();
    }

    oled_on();

    if (is_keyboard_master()) {
        // render_space();  // Renders a static log
        if (isOff) {
            z_anim();
        } else {
            render_falling_symbols();
        }
    } else {
        print_status_narrow();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (isOff && keycode != QK_GESC) {
        return false;
    }

    switch (keycode) {
        case QK_GESC:
            if (record->event.pressed) {
                // Key is pressed, start the timer
                off_timer = timer_read();
                isOff     = false;
            } else {
                // Key is released, check the elapsed time
                if (timer_elapsed(off_timer) > 1000) {
                    // Key was held for more than 2 seconds
                    // Add your custom action here
                    isOff = true;
                }
            }
            return true;
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                // update_tri_layer(_LOWER, _RAISE);
            } else {
                layer_off(_LOWER);
                // update_tri_layer(_LOWER, _RAISE);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                // update_tri_layer(_LOWER, _RAISE);
            } else {
                layer_off(_RAISE);
                // update_tri_layer(_LOWER, _RAISE);
            }
            return false;
        case KC_D_MUTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_MEH));
                register_code(KC_UP);
            } else {
                unregister_mods(mod_config(MOD_MEH));
                unregister_code(KC_UP);
            }
            return false;
    }

#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    return true;
}

uint8_t array[] = {1, 3, 5, 7, 9, 11, 13, 15, 20, 21, 27, 29, 34, 35, 41, 43, 45, 47, 49, 51};

void rgblight_before_set(void) {
    uint8_t hue = rgblight_get_hue();
    // hue += 1; // Increment hue to cycle through colors
    // if (hue > 255) hue = 0;

    int     arrLen    = sizeof(array) / sizeof(array[0]);
    uint8_t skipIndex = 0;
    uint8_t over      = 0;

    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        // Convert HSV to RGB

        // Set the LED color
        uint8_t skip = -1;
        if (skipIndex < arrLen) {
            skip = array[skipIndex];
        } else {
            skipIndex = 0;
            over      = 52;
        }
        if (skip > 0 && i == skip + over) {
            skipIndex++;

            uint8_t index = i;
#ifdef RGBLIGHT_LED_MAP
            if (index <= 51) {
                index = 51 - index;
            }
#endif
            rgblight_h_at(hue, index);
        }
    }
}

#ifdef CUSTOM_RGB

rgb_led_t rgb_matrix_ws2812_array[WS2812_LED_COUNT];
bool      ws2812_dirty = false;

static void init(void) {
    ws2812_init();
    ws2812_dirty = false;
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable   = true;
    debug_keyboard = true;
    init();
}

static void flush(void) {
    if (ws2812_dirty) {
        ws2812_setleds(rgb_matrix_ws2812_array, WS2812_LED_COUNT);
        ws2812_dirty = false;
    }
}

// Set an led in the buffer to a color
static inline void setled(int i, uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t k_rgb_matrix_split[2] = WS2812_SPLIT;
    if (!is_keyboard_master()) {
        if (i >= k_rgb_matrix_split[0]) {
            i -= k_rgb_matrix_split[0];
        } else {
            return;
        }
    } else if (i >= k_rgb_matrix_split[0]) {
        return;
    }

    if (rgb_matrix_ws2812_array[i].r == r && rgb_matrix_ws2812_array[i].g == g && rgb_matrix_ws2812_array[i].b == b) {
        return;
    }

    ws2812_dirty                 = true;
    rgb_matrix_ws2812_array[i].r = r;
    rgb_matrix_ws2812_array[i].g = g;
    rgb_matrix_ws2812_array[i].b = b;
}

RGB hsv_to_rgb_impl(HSV hsv) {
    RGB      rgb;
    uint8_t  region, remainder, p, q, t;
    uint16_t h, s, v;

    if (hsv.s == 0) {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;

        return rgb;
    }

    h = hsv.h;
    s = hsv.s;

    v = hsv.v;

    region    = h * 6 / 255;
    remainder = (h * 2 - region * 85) * 3;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region) {
        case 6:
        case 0:
            rgb.r = v;
            rgb.g = t;
            rgb.b = p;
            break;
        case 1:
            rgb.r = q;
            rgb.g = v;
            rgb.b = p;
            break;
        case 2:
            rgb.r = p;
            rgb.g = v;
            rgb.b = t;
            break;
        case 3:
            rgb.r = p;
            rgb.g = q;
            rgb.b = v;
            break;
        case 4:
            rgb.r = t;
            rgb.g = p;
            rgb.b = v;
            break;
        default:
            rgb.r = v;
            rgb.g = p;
            rgb.b = q;
            break;
    }

    return rgb;
}

uint8_t array[] = {1, 3, 5, 7, 9, 11, 13, 15, 20, 21, 27, 29, 34, 35, 41, 43, 45, 47, 49, 51};
void    custom_rgb_effect(void) {
    static uint8_t hue        = 0;
    static uint8_t brightness = 100; // Max brightness

    hue += 1; // Increment hue to cycle through colors
    if (hue > 255) hue = 0;

    int     arrLen    = sizeof(array) / sizeof(array[0]);
    uint8_t skipIndex = 0;

    uint8_t       led_min_index         = 0;
    uint8_t       led_max_index         = WS2812_LED_COUNT;
    const uint8_t k_rgb_matrix_split[2] = WS2812_SPLIT;
    if (is_keyboard_master() && (led_max_index > k_rgb_matrix_split[0])) led_max_index = k_rgb_matrix_split[0];
    if (!(is_keyboard_master()) && (led_min_index < k_rgb_matrix_split[0])) led_min_index = k_rgb_matrix_split[0];

    for (uint8_t i = led_min_index; i < led_max_index; i++) {
        // Convert HSV to RGB
        HSV hsv = {.h = hue, .s = 255, .v = brightness};

        uint8_t skip = -1;
        if (skipIndex < arrLen) {
            skip = array[skipIndex];
        }
        if (i == skip) {
            hsv.h = 100;
            skipIndex++;
        }

        RGB rgb = hsv_to_rgb_impl(hsv);

        // Set the LED color
        setled(i, rgb.r, rgb.g, rgb.b);
    }

    flush();
}

void matrix_scan_user_(void) {
    custom_rgb_effect(); // Call the custom effect in the matrix scan loop
}
#endif