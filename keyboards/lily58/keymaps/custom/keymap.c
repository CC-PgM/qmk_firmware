#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _SYMBOL 1
#define _MOVING 2
#define _TENKEY 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOL,
  MOVING,
  TENKEY,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  F13  |    |  F14  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |SYMBOL| /Space  /       \Enter \  |MOVING|BackSP|  =+  |
 *                   |      |      |LNG_EN|/       /         \      \ |LNG_JA|      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_CAPS, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_F13,   KC_F14,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS, \
              KC_LALT, KC_LGUI, LT(_SYMBOL, KC_F13), KC_SPC,   KC_ENT, LT(_MOVING, KC_F14), KC_BSPC, KC_EQL \
),
/* SYMBOL
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | TRNS | TRNS | TRNS | / TRNS  /       \ TRNS \  |  TO  | TRNS | DEL  |
 *                   |      |      |      |/       /         \      \ |TENKEY|      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SYMBOL] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
                             _______, _______, _______, _______, _______, TO(_TENKEY), _______, KC_DEL \
),
/* MOVING
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |BackSP| DEL  |                    |BackSP| Del  |Insert|      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  Up  |      | Home | End  |                    | Home | End  | PgUp |PgDown|      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL | Left | Down | Right| PgUp |PgDown|-------.    ,-------| Left | Down |  Up  | Right|      | RCTRL|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|      |      |      |Insert|      |-------|    |-------|      |      |      |      |      |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | TRNS | TRNS |  TO  | / TRNS  /       \ TRNS \  | TRNS | TRNS | DEL  |
 *                   |      |      |TENKEY|/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_MOVING] = LAYOUT( \
  KC_ESC,   XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, KC_DEL,                    KC_BSPC, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_TAB,   XXXXXXX, KC_UP,   XXXXXXX, KC_HOME, KC_END,                    KC_HOME, KC_END,  KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX, \
  KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, KC_PGDN,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_RCTL, \
  KC_LSFT,  XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, \
                          _______, _______, TO(_TENKEY), _______, _______, _______, _______, _______ \
),
/* TENKEY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |NumLck|                    |      |  n7  |  n8  |  n9  |  *   |  /   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  Up  |      |      |CapLck|                    |      |  n4  |  n5  |  n6  |  +   |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL | Left | Down | Right|      |SclLck|-------.    ,-------|      |  n1  |  n2  |  n3  |  =   | RCTRL|
 * |------+------+------+------+------+------|  F13  |    |  F14  |------+------+------+------+------+------|
 * |LShift|      |      |      |      |      |-------|    |-------|      |  n0  |  .   |  ,   | Enter|RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | TRNS | TRNS |  TO  | / TRNS  /       \ TRNS \  |  TO  | TRNS | TRNS |
 *                   |      |      |QWERTY|/       /         \      \ |QWERTY|      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_TENKEY] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_PSLS, \
  XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_PMNS, \
  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_RCTL, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F13,  KC_F14,  XXXXXXX, KC_P0,   KC_PDOT, KC_PCMM, KC_PENT, KC_RSFT, \
                         _______, _______, TO(_QWERTY), _______, _______, TO(_QWERTY), _______, _______ \
  )
};

int RGB_current_mode;

// Setting TENKEY layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case SYMBOL:
      if (record->event.pressed) {
        layer_on(_SYMBOL);
        update_tri_layer_RGB(_SYMBOL, _MOVING, _TENKEY);
      } else {
        layer_off(_SYMBOL);
        update_tri_layer_RGB(_SYMBOL, _MOVING, _TENKEY);
      }
      return false;
      break;
    case MOVING:
      if (record->event.pressed) {
        layer_on(_MOVING);
        update_tri_layer_RGB(_SYMBOL, _MOVING, _TENKEY);
      } else {
        layer_off(_MOVING);
        update_tri_layer_RGB(_SYMBOL, _MOVING, _TENKEY);
      }
      return false;
      break;
    case TENKEY:
        if (record->event.pressed) {
          layer_on(_TENKEY);
        } else {
          layer_off(_TENKEY);
        }
        return false;
        break;
  }
  return true;
}
