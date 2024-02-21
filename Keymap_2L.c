#include QMK_KEYBOARD_H
#include "keymap_nordic.h"
enum layers {
  _DEFAULT,
  _LOWER
};

#define LOWER MO(_LOWER)

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 3500) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
} 

enum {
    TD_DOT_ESC = 0,
	TD_PERC_PAST,
	TD_SLSH_BSLS,
	TD_EQUAL_PLUS,
	TD_AT_QUOT,
	TD_LPRN_RPRN
};
 qk_tap_dance_action_t tap_dance_actions[] = {
	   [TD_DOT_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ESC),
	   [TD_PERC_PAST]  = ACTION_TAP_DANCE_DOUBLE(KC_PERC, KC_PAST),
	   [TD_SLSH_BSLS]  = ACTION_TAP_DANCE_DOUBLE(NO_SLSH, NO_BSLS),
	   [TD_EQUAL_PLUS]  = ACTION_TAP_DANCE_DOUBLE(NO_EQL, NO_PLUS),
	   [TD_AT_QUOT]  = ACTION_TAP_DANCE_DOUBLE(NO_AT, NO_QUOT),
	   [TD_LPRN_RPRN]  = ACTION_TAP_DANCE_DOUBLE(NO_LPRN, NO_RPRN)
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default
 * ,------------------------------------------------------------------------------------.------.
 * | Entr |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   Ã…  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+-------|------|
 * |LowTab|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ã–  |   Ã„ | Entr |
 * |------+------+------+------+------+------|------+------+------+------+------+-------|------'
 * | Ctrl |   Z  |   X  |   C  |   V  |    Space    |   B  |   N  |   M  | .ESC | ,Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+-------'
 */
[_DEFAULT] = LAYOUT_2u_space(
    KC_ENT,             KC_Q, KC_W, KC_E, KC_R, KC_T,  KC_Y, KC_U, KC_I, KC_O,            KC_P,  NO_AM,   KC_BSPC,
    LT(_LOWER, KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,  KC_H, KC_J, KC_K, KC_L,            NO_AE, NO_OSLH, KC_ENT,
    KC_LCTL,            KC_Z, KC_X, KC_C, KC_V, KC_SPC,KC_B, KC_N, KC_M, TD(TD_DOT_ESC), RSFT_T(KC_COMM)
),

/* Lower - Numbers and some symbols
 * ,------------------------------------------------------------------------------------------.
 * |  DEL |  CAD |  UP  |RGB_VD|RGB_VI|  /\  |  ()  |   7  |   8  |   9  |   !  |  ?   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------|
 * |      | LEFT | DOWN |RIGHT | GUI+L|  %*  |  =+  |   4  |   5  |   6  |   _  |  @"  | PrScr|
 * |------+------+------+------+------+------+------+------+------+------+------+------|------'
 * |  F1  |  F2  |  F3  |  F4  |  F5  |      0      |   1  |   2  |   3  |   -  |  ;   |
 * `------+------+------+------+------+------+------+------+------+------+------+------'
 */
[_LOWER] = LAYOUT_2u_space(
    KC_DEL, LALT(LCTL(KC_DEL)),  KC_UP, RGB_VAD, RGB_VAI, TD(TD_SLSH_BSLS), TD(TD_LPRN_RPRN), KC_7,  KC_8,  KC_9,    KC_EXLM, NO_QUES, _______,
    _______,  KC_LEFT,  KC_DOWN, KC_RIGHT, LGUI(KC_L),TD(TD_PERC_PAST), TD(TD_EQUAL_PLUS), KC_4,  KC_5,  KC_6,   NO_UNDS,  TD(TD_AT_QUOT),   KC_PSCREEN,
    KC_F1, KC_F2,    KC_F3,   KC_F4, KC_F5, KC_0,    KC_1,    KC_2,  KC_3,  NO_MINS, NO_SECT
),
};
void encoder_update_user(uint8_t index, bool clockwise) {
if (clockwise) {
if (!is_alt_tab_active) {
is_alt_tab_active = true;
register_code(KC_LALT);
}
alt_tab_timer = timer_read();
tap_code16(KC_TAB);
} else {
alt_tab_timer = timer_read();
tap_code16(S(KC_TAB));
}
};
