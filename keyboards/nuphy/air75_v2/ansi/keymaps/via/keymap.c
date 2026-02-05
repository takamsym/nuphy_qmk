/*
 * NuPhy Air75 v2 - JIS Layout Fix (Rollover Fixed)
 */

#include QMK_KEYBOARD_H
#include "ansi.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    LAYER_4
};

// ==========================================================
// Keychron互換 Key Overrides ロジック (ロールオーバー対策版)
// ==========================================================

#define WIN_MASK ((1 << WIN_BASE) | (1 << WIN_FN))
#define NEG_MODS (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)

// ★修正点: .options を 0 (デフォルト) に変更しました。
// これにより、次のキーが押された瞬間に前のキーのOverride(Shift解除等)がリセットされ、
// 正しいShift状態が次のキーに適用されるようになります。

#define KO_SINGLE(trigger_key, replacement_key) \
    { \
        .trigger_mods = 0, \
        .layers = WIN_MASK, \
        .negative_mod_mask = (NEG_MODS | MOD_MASK_SHIFT), \
        .suppressed_mods = 0, \
        .options = 0, \
        .trigger = (trigger_key), \
        .replacement = (replacement_key) \
    }

#define KO_SHIFT(trigger_key, replacement_key) \
    { \
        .trigger_mods = MOD_MASK_SHIFT, \
        .layers = WIN_MASK, \
        .negative_mod_mask = NEG_MODS, \
        .suppressed_mods = MOD_MASK_SHIFT, \
        .options = 0, \
        .trigger = (trigger_key), \
        .replacement = (replacement_key) \
    }

// --- 変換定義 ---

// 1. カッコとバックスラッシュの左右
const key_override_t lbrc_single = KO_SINGLE(KC_LBRC, KC_RBRC);         // [
const key_override_t lbrc_shift  = KO_SHIFT(KC_LBRC, S(KC_RBRC));       // {
const key_override_t rbrc_single = KO_SINGLE(KC_RBRC, KC_BSLS);         // ]
const key_override_t rbrc_shift  = KO_SHIFT(KC_RBRC, S(KC_BSLS));       // }
const key_override_t bsls_single = KO_SINGLE(KC_BSLS, KC_INT1);         // \ (Ro)
const key_override_t bsls_shift  = KO_SHIFT(KC_BSLS, S(KC_INT3));       // |

// 2. 記号類
const key_override_t eql_single  = KO_SINGLE(KC_EQL, S(KC_MINS));       // =
const key_override_t eql_shift   = KO_SHIFT(KC_EQL, S(KC_SCLN));        // +
const key_override_t quo_single  = KO_SINGLE(KC_QUOT, S(KC_7));         // '
const key_override_t quo_shift   = KO_SHIFT(KC_QUOT, S(KC_2));          // "
const key_override_t grv_single  = KO_SINGLE(KC_GRV, S(KC_LBRC));       // `
const key_override_t grv_shift   = KO_SHIFT(KC_GRV, S(KC_EQL));         // ~

// 3. 数字行のShift
const key_override_t at_override   = KO_SHIFT(KC_2, KC_LBRC);    // @
const key_override_t hash_override = KO_SHIFT(KC_3, S(KC_3));    // #
const key_override_t caret_override= KO_SHIFT(KC_6, KC_EQL);     // ^
const key_override_t amp_override  = KO_SHIFT(KC_7, S(KC_6));    // &
const key_override_t ast_override  = KO_SHIFT(KC_8, S(KC_QUOT)); // *
const key_override_t lpar_override = KO_SHIFT(KC_9, S(KC_8));    // (
const key_override_t rpar_override = KO_SHIFT(KC_0, S(KC_9));    // )
const key_override_t under_override= KO_SHIFT(KC_MINS, S(KC_INT1)); // _
const key_override_t col_override  = KO_SHIFT(KC_SCLN, KC_QUOT); // :

// リスト登録
const key_override_t **key_overrides = (const key_override_t *[]) {
    &lbrc_single, &lbrc_shift,
    &rbrc_single, &rbrc_shift,
    &bsls_single, &bsls_shift,
    &eql_single,  &eql_shift,
    &quo_single,  &quo_shift,
    &grv_single,  &grv_shift,
    &at_override,
    &hash_override,
    &caret_override,
    &amp_override,
    &ast_override,
    &lpar_override,
    &rpar_override,
    &under_override,
    &col_override,
    NULL
};

// --- キーマップ定義 ---

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_84(
		KC_ESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   MAC_PRT, KC_DEL,  KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,     KC_4,       KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,       KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,     KC_F,       KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,     KC_C,       KC_V,      KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                                  KC_SPC,                             KC_RGUI, MO(MAC_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [MAC_FN] = LAYOUT_ansi_84(
		_______,  KC_BRID, KC_BRIU, MAC_TASK, MAC_SEARCH, MAC_VOICE, MAC_DND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, MAC_PRTA, KC_INS, _______,
        _______, LNK_BLE1, LNK_BLE2, LNK_BLE3, LNK_RF,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  QK_BOOT,  SLEEP_MODE, BAT_SHOW,          _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,             _______,
        _______,           _______,  _______,  _______,  _______,  _______,  _______,  MO(LAYER_4), RGB_SPD, RGB_SPI, _______,           _______,    RGB_VAI, _______,
        _______, _______,  _______,                                _______,                                _______,  _______,  _______,  RGB_MOD,    RGB_VAD, RGB_HUI
    ),
    [WIN_BASE] = LAYOUT_ansi_84(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_DEL,  KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,          KC_LGUI, LALT_T(KC_INT5),                KC_SPC,             RALT_T(KC_INT4), MO(WIN_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [WIN_FN] = LAYOUT_ansi_84(
        _______, KC_BRID,  KC_BRIU,  _______,  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______, KC_INS, _______,
        _______, LNK_BLE1, LNK_BLE2, LNK_BLE3, LNK_RF,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  QK_BOOT,  SLEEP_MODE, BAT_SHOW,       _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,          _______,
        _______,           _______,  _______,  _______,  _______,  _______,  _______,  MO(LAYER_4), RGB_SPD, RGB_SPI, _______,           _______, RGB_VAI, _______,
        _______, _______,  _______,                                _______,                                _______,  _______,  _______,  RGB_MOD,    RGB_VAD, RGB_HUI
    ),
    [LAYER_4] = LAYOUT_ansi_84(
        _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______, _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,          _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,          _______,
        _______,           _______,  _______,  _______,  _______,  _______,  _______,  _______,  SIDE_SPD, SIDE_SPI, _______,            _______, SIDE_VAI, _______,
        _______, _______,  _______,                                _______,                                _______,  _______,  _______,  SIDE_MOD, SIDE_VAD, SIDE_HUI
    )
};