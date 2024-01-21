#include QMK_KEYBOARD_H
#include "keymap_nordic.h"
enum layers {
  _DEFAULT,
  _LOWER,
  _RAISE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 2000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
} 

enum {
    TD_DOT_COLN = 0
};
 qk_tap_dance_action_t tap_dance_actions[] = {
	   [TD_DOT_COLN]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, NO_COLN)
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default
 * ,------------------------------------------------------------------------------------.------.
 * | Entr |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   Å   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+-------|------|
 * |LowEsc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |   Ä   | Entr |
 * |------+------+------+------+------+------|------+------+------+------+------+-------|------'
 * | Ctrl |   Z  |   X  |   C  |   V  |    Space    |   B  |   N  |   M  |  .:  | ,Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+-------'
 */
[_DEFAULT] = LAYOUT_2u_space(
    KC_ENT,             KC_Q, KC_W, KC_E, KC_R, KC_T,  KC_Y, KC_U, KC_I, KC_O,            KC_P,  NO_AM,   KC_BSPC,
    LT(_LOWER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G,  KC_H, KC_J, KC_K, KC_L,            NO_AE, NO_OSLH, KC_ENT,
    KC_LCTL,            KC_Z, KC_X, KC_C, KC_V, KC_SPC,KC_B, KC_N, KC_M, TD(TD_DOT_COLN), RSFT_T(KC_COMM)
),

/* Lower - Numbers and some symbols
 * ,------------------------------------------------------------------------------------------.
 * |  DEL |  CAD |   "  |   \  |   /  |   (  |   )  |   7  |   8  |   9  |   !  |  ?   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------|
 * |      |RGB_VD|RGB_VI|   %  |   *  |   =  |   +  |   4  |   5  |   6  |   _  |  @   | PrScr|
 * |------+------+------+------+------+------+------+------+------+------+------+------|------'
 * |   <  |   >  |   &  |   |  |   $  |      0      |   1  |   2  |   3  |   -  |  ;   |
 * `------+------+------+------+------+------+------+------+------+------+------+------'
 */
[_LOWER] = LAYOUT_2u_space(
    KC_DEL, LALT(LCTL(KC_DEL)), NO_QUOT, NO_BSLS,  KC_SLSH, NO_LBRC, NO_RBRC, KC_7,  KC_8,  KC_9,    KC_EXLM, NO_QUES, _______,
    _______, RGB_VAD, RGB_VAI,  KC_PERC,  KC_PAST, KC_EQUAL, NO_PLUS, KC_4,  KC_5,  KC_6,    KC_UNDS,  NO_AT,   KC_PSCREEN,
    NO_HALF, NO_SECT, NO_AMPR, NO_LCBR, NO_DLR, KC_0,    KC_1,    KC_2,  KC_3,  NO_MINS, NO_SECT
),

/* Raise - AltGred Characters and more symbols
 * ,------------------------------------------------------------------------------------------.
 * |      |      |   =  |   "  |  \   |   /  |   !  |   %  |   &  |   (  |   )  |  ?   |  DEL |
 * |------+------+------+------+------+------+------+------+------+------+------+------|------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  -   |   _  |  @   | PrScr|
 * |------+------+------+------+------+------+------+------+------+------+------+------|------'
 * |      |   <  |   >  |RGB_VD|RGB_VI|             |      |      |      |      |  ;   |
 * `------+------+------+------+------+------+------+------+------+------+------+------'
 */
[_RAISE] = LAYOUT_2u_space(
    _______, _______, KC_EQUAL, NO_QUOT, NO_BSLS, NO_SLSH, KC_EXLM, KC_PERC, NO_AMPR, NO_LBRC, NO_RBRC, NO_QUES, KC_DEL,
    _______, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   NO_MINS, NO_UNDS, NO_AT,   KC_PSCREEN,
    _______, NO_HALF, NO_SECT,  RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, NO_SCLN
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