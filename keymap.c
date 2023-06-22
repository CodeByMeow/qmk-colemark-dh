#include QMK_KEYBOARD_H
#include "oled.c"
#include "encoder.c"

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _COLEMAK,
    _LOWER,
    _RAISE,
};


// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_N RCTL_T(KC_N)
#define HOME_E RSFT_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * COLEMAK
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | TAB  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   '  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | LCTL |HOME_A|HOME_R|HOME_S|HOME_T|  G   |                    |   M  |HOME_N|HOME_E|HOME_I|HOME_O|  ;  |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  | ESC  |
     * `-----------------------------------------/        /     \      \-----------------------------------------'
     *            |      | LALT  | LGUI  |      |/LT(LOWER,
     *                                           ENTER) /        \Space \  |RAISE | RGUI |      |      |
     *            |      |      |      |      |/       /          \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */

    [_COLEMAK] = LAYOUT(XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT, KC_BSPC, 
            KC_LCTL, HOME_A, HOME_R, HOME_S, HOME_T, KC_G, KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_SCLN,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_MUTE, XXXXXXX, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
            XXXXXXX, XXXXXXX, KC_LGUI, XXXXXXX, LT(_LOWER, KC_ENT), KC_SPC, MO(_RAISE), XXXXXXX, XXXXXXX, XXXXXXX),
    /* LOWER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | TRNS |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | TRNS  |     |      |      |      |      |-------.    ,-------|      |KC_DOWN|KC_UP|KC_RIGHT|     | DEL |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * | TRNS |      |      |      |      |      |-------|    |-------|      |KC_LEFT|      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |      | LALT  | LGUI  |      |/LT(LOWER,
     *                                           ENTER) /        \Space \  |RAISE | RGUI |      |      |
     *            |      |      |      |      |/       /          \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_LOWER] = LAYOUT(XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F12, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, KC_DEL, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, KC_LEFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
    /* RAISE
     * ,----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | TRNS |  !  |   @  |   #   |   $  |  %   |                    |  ^   |   &  |   *  |   (  |   )  | TRNS |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | TRNS | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|   -  |   =  |   [  |   ]  |  \   |  `   |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * | TRNS |      |      |      |      |      |-------|    |-------|   _  |   +  |   {  |   }  |  |   |  ~   |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |      | LALT  | LGUI  |      |/LT(LOWER,
     *                                           ENTER) /        \Space \  |RAISE | RGUI |      |      |
     *            |      |      |      |      |/       /          \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_RAISE] = LAYOUT(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)};
