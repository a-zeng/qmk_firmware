/* Copyright 2021 duoshock
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

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FN,
    _TWO,
    _THREE
};

// Light LED 20 (CAPS lock key) in green when caps lock is active
const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {20, 1, HSV_RED}       // Light 4 LEDs, starting with LED 6
    // {12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
);
// Default layer color
const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 0, HSV_AZURE_}
);
// Light all the changed keys in purple when function layer is active
const rgblight_segment_t PROGMEM function_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_PURPLE},  // 1-6 are left underglow
    {39, 6, HSV_PURPLE},   // 39-44 are right underglow
    {38, 1, HSV_PURPLE}, // 38 is FN
    {7, 6, HSV_PURPLE},   // 7-12 are number keys 1-6
    {45, 6, HSV_PURPLE}   // 45-51 are number keys 7-10 and - and =
);
// Light all the changed keys in purple when function layer is active
const rgblight_segment_t PROGMEM layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {15, 1, HSV_BLUE}, // 15 is W
    {21, 3, HSV_BLUE} // 21-23 are A, S, and D
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer,
    base_layer,    // Overrides caps lock layer
    function_layer,    // Overrides other layers
    layer2_layer     // Overrides other layers
);
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _BASE));
    return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(3, layer_state_cmp(state, _TWO));
    return state;
}


// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// 	[0] = KEYMAP(
// 		M(0), M(1)
// 	),
// };

// const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
// 	if (record->event.pressed) {
// 		switch(id) {
// 			case 0:
// 				return MACRO(T(SPC), W(4), T(LCTL), END);
// 		}
// 	}
// 	return MACRO_NONE;
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 *          .---------------------------.          .-------------------------------.        .---.
 *          |Esc|  1|  2|  3|  4|  5|  6|          |  7|  8|  9|  0|  -|  =|`  |Bsp|        |EC |
 *          |-------------------------.          .---------------------------------|        |---|
 *          |Tab  |  Q|  W|  E|  R|  T|          |  Y|  U|  I|  O|  P|  [|  ]|  \  |        | ` |
 *   .---.  |-------------------------.          '---------------------------------|        |---|
 *   |PgU|  |CapsL |  A|  S|  D|  F|  G|          |  H|  J|  K|  L|  ;|  :|   Retn |        |Del|
 *   |---|  |----------------------------.        '--------------------------------|  .---. '---'
 *   |PdD|  |Shft    |  Z|  X|  C|  V|  B|          |  N|  M|  ,|  .|  /|  Shift|     |Up |
 *   |---|  |----------------------------|          |---------------------------' .-----------.
 *   |M2 |  |Ctl |Gui |Alt |Fn0 |Space   |          |   Space |  Alt |   Ctl|     |Lef|Dow|Rig|
 *   '---'  '----------------------------'          '-----------------------'     '-----------'
 */

[_BASE] = LAYOUT_rspace_split_bksp(
            KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC,    KC_MUTE,
            KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,                     KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,   KC_BSLS,   KC_GRV,
    KC_PGUP,KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G,                     KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,    KC_ENT,         KC_DEL,
    KC_PGDN,KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                     KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,                     KC_UP,
    TG(2),  KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_SPC,                   KC_SPC, KC_RALT, KC_RCTL,                               KC_LEFT, KC_DOWN, KC_RGHT
),

[_FN] = LAYOUT_rspace_split_bksp(
                KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS,    KC_F13,
                KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
    RGB_HUI,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,         KC_TRNS,
    RGB_HUD,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS
),
[_TWO] = LAYOUT_rspace_split_bksp(
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,         KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_NO,   KC_TRNS, KC_NO,   KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS
),
[_THREE] = LAYOUT_rspace_split_bksp(
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,         KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                              KC_TRNS, KC_TRNS, KC_TRNS,                               KC_TRNS, KC_TRNS, KC_TRNS
),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Master Left */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Master Right */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}


#ifdef OLED_ENABLE
void suspend_power_down_user(void) {
    oled_off();
    // rgblight_suspend();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_90;
    }

    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,224,224,224,224,224,224,224,224,224,224,224,224,224,224,192,192,128,128,192,192,224,224,224,224,224,224,224,224,192,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 15,  3,  1,  0,  1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,254,254,  0,  0,  0,  0,  0,  0,254,254,254,  0,  0,  0,254,254,254,252,248,224,192,128,224,248,252,254,254,254,  0,  0,128,128,128,128,128,128,  0, 14, 14, 14, 14,142,238,254,254,126, 30,  4,224,248,252, 62, 30, 14, 14, 14, 30, 62,252,248,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,240,192,128,  0,128,255,255,255,255,255,255,255,255,255,255,255,255,255,255,127, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 63, 63,124,112,112,112,112,124, 63, 63, 15,  0,  0,  0,127,127,127,  0,  1,  7, 15, 15,  7,  1,  0,127,127,127,  0,  0,  3,  3,  3,  3,  3,  3,  1,  0,112,124,126, 63, 15,  3,  1,  0,  0,  0, 15, 31, 63,124,120,112,112,112,120,124, 63, 31, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3,  3,  1,  1,  3,  3,  7,  7,  7,  7,  7,  7,  7,  7,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


// 32 * 18 Merge logos
// static const char PROGMEM merge_logo[] = {
//     0xf8, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0e,
//     0x06, 0x04, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xc0,
//     0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xc0,
//     0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f,
//     0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
//     0x01, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00
// };


// 32x18 Snom
static const char PROGMEM merge_logo[] = {
    0,  0,  0,  0,  0,128,128, 64, 64, 64,112,136,  4,  2,  1,  1,130,148,136,136,132,130,130, 92, 32, 32, 16, 16, 16,144, 96,  0,  0,240,140,  2,225, 32,  0,  0,  0,  0,192,192,  1, 14,248,  0,  0,  0,  0, 40, 36, 34, 65,128,  8, 20, 34, 66, 97,162, 36, 24,  0,  0,  0,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  1,  1,  1,  1,  1,  1,  0
};

uint8_t current_wpm = 0;

static void print_status_narrow(void) {
    oled_set_cursor(0,1);
    oled_write_raw_P(merge_logo, sizeof(merge_logo));
    oled_set_cursor(0,5);
    oled_write_P(PSTR("-----"), false);
    oled_set_cursor(0,6);
    oled_write_P(PSTR("LYR "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("0"), false);
            break;
        case _FN:
            oled_write_P(PSTR("1"), false);
            break;
        case _TWO:
            oled_write_P(PSTR("2"), false);
            break;
        case _THREE:
            oled_write_P(PSTR("3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("CAP "), false);
    oled_write_P(PSTR("."), led_usb_state.caps_lock);
    oled_write_P(PSTR("NUM "), false);
    oled_write_P(PSTR("."), led_usb_state.num_lock);
    oled_write_P(PSTR("SCR "), false);
    oled_write_P(PSTR("."), led_usb_state.scroll_lock);
    //oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("-----"), false);

    // WPM counter Start
    char wpm_str[5];
    oled_set_cursor(0,13);
    wpm_str[4] = '\0';
    uint8_t n = current_wpm;
    wpm_str[3] = '0' + n % 10;
    wpm_str[2] = '0' + (n /= 10) % 10;
    wpm_str[1] = '0' + n / 10;
    wpm_str[0] = ' ';
    oled_write(wpm_str, false);
    oled_set_cursor(0,14);
    oled_write(" WPM ", false);
    // WPM counter End
}

bool oled_task_user(void) {
    current_wpm = get_current_wpm();
    if (is_keyboard_master()) {
        print_status_narrow();
        //render_logo();
    } else {
        render_logo();
        //print_status_narrow();
    }
    return false;
}

#endif

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_AZURE_);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
#endif

/* RGB Timeout behaves similar to OLED Timeout where it turns off underglow 
lighting on your QMK board after X seconds of inactivity. The logic is 
best described by this reddit comment - https://bit.ly/3zCYIRl
To begin, add the following variables and function definitions to your keymap.c file */

static uint16_t key_timer; // timer to track the last keyboard activity
static void refresh_rgb(void); // refreshes the activity timer and RGB, invoke whenever activity happens
static void check_rgb_timeout(void); // checks if enough time has passed for RGB to timeout
bool is_rgb_timeout = false; // store if RGB has timed out or not in a boolean


void refresh_rgb() {
  key_timer = timer_read(); // store time of last refresh
  if (is_rgb_timeout) { // only do something if rgb has timed out
    print("Activity detected, removing timeout\n");
    is_rgb_timeout = false;
    rgblight_wakeup();
  }
}

void check_rgb_timeout() {
  if (!is_rgb_timeout && timer_elapsed(key_timer) > RGBLIGHT_TIMEOUT) {
    rgblight_suspend();
    is_rgb_timeout = true;
  }
}


/* Then, call the above functions from QMK's built in post processing functions like so */

/* Runs at the end of each scan loop, check if RGB timeout has occured */
void housekeeping_task_user(void) {
  #ifdef RGBLIGHT_TIMEOUT
  check_rgb_timeout();
  #endif
  
  /* rest of the function code here */
}

/* Runs after each key press, check if activity occurred */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef RGBLIGHT_TIMEOUT
  if (record->event.pressed) refresh_rgb();
  #endif

  /* rest of the function code here */
}

/* Runs after each encoder tick, check if activity occurred */
void post_encoder_update_user(uint8_t index, bool clockwise) {
  #ifdef RGBLIGHT_TIMEOUT
  refresh_rgb();
  #endif
  
  /* rest of the function code here */
}