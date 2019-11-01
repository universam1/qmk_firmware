#include QMK_KEYBOARD_H
#include "universam.h"

extern keymap_config_t keymap_config;
extern uint8_t         is_master;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif
#ifdef OLED_DRIVER_ENABLE
static uint32_t        oled_timer = 0;
static char     keylog_str[6]   = {};
static uint16_t log_timer       = 0;
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

void add_keylog(uint16_t keycode);
#endif

enum crkbd_keycodes { RGBRST = NEW_SAFE_RANGE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_wrapper( \
    KC_ESC,        KC_Q,        KC_W,  KC_E,  KC_R,  KC_T,                  KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,             KC_MINS,
    ALT_T(KC_TAB), KC_A,        KC_S,  KC_D,  KC_F,  KC_G,                  KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN,          RALT_T(KC_QUOT),
    OS_LSFT,       CTL_T(KC_Z), KC_X,  KC_C,  KC_V,  KC_B,                  KC_N,  KC_M,  KC_COMM, KC_DOT,  RCTL_T(KC_SLASH), OS_RSFT,
                      KC_GRAVE,  LT(_LOWER, KC_BSPC), KC_SPC,            KC_ENT, LT(_RAISE, KC_DEL), OSM(MOD_RGUI)
  ),

  [_MODS] = LAYOUT_wrapper(
      _______, ___________________BLANK___________________,                  ___________________BLANK___________________, _______,
      _______, ___________________BLANK___________________,                  ___________________BLANK___________________, _______,
      KC_LSFT, ___________________BLANK___________________,                  ___________________BLANK___________________, KC_RSFT,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_LOWER] = LAYOUT_wrapper(
    KC_F11,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F11,
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_RAISE] = LAYOUT_wrapper( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,       KC_0, _______,
    _______, ___________________BLANK___________________,                    ___________________BLANK___________________, KC_BSLS,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_wrapper( \
    KC_MAKE, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG,                    KC_ASDN, KC_ASUP, KC_ASRP, KC_ASON, KC_ASOFF, KC_RESET,
    VRSN,    MU_TOG , CK_TOGG, AU_ON,   AU_OFF,  CG_NORM,                    CG_SWAP, QWERTY,  COLEMAK, DVORAK,  WORKMAN, EEP_RST,
    MG_NKRO, RGB_RMOD,RGB_HUD,RGB_SAD, RGB_VAD, KC_RGB_T,                    MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, RGB_IDL,
                                     _______, _______, _______,        _______, _______, TG(_MODS)
  )
};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
        add_keylog(keycode);
#endif
#ifndef SPLIT_KEYBOARD
        if (keycode == RESET && !is_master) {
            return false;
        }
#endif
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = 4; i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        //add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR(" COLE"), false);
            break;
        case _DVORAK:
            oled_write_P(PSTR(" DVRK"), false);
            break;
        case _WORKMAN:
            oled_write_P(PSTR(" WKMN"), false);
            break;
        case _NORMAN:
            oled_write_P(PSTR(" NORM"), false);
            break;
        case _MALTRON:
            oled_write_P(PSTR(" MLTN"), false);
            break;
        case _EUCALYN:
            oled_write_P(PSTR(" ECLN"), false);
            break;
        case _CARPLAX:
            oled_write_P(PSTR(" CRPX"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE));
    oled_write_P(PSTR(" Mods"), layer_state_is(_MODS));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}

void render_user_status(void) {
    oled_write_P(PSTR("USER:"), false);
    oled_write_P(PSTR(" Anim"), userspace_config.rgb_matrix_idle_anim);
    oled_write_P(PSTR(" Layr"), userspace_config.rgb_layer_change);
    oled_write_P(PSTR(" Nuke"), userspace_config.nuke_switch);
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_bootmagic_status();
    render_user_status();

    render_keylogger_status();
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_layer_state();
    render_mod_status(get_mods()|get_oneshot_mods());

    render_keylogger_status();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    update_log();
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif

uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case ALT_T(KC_A):
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

void check_default_layer(uint8_t mode, uint8_t type) {
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            rgb_matrix_layer_helper(HSV_CYAN, mode, rgb_matrix_config.speed, type);
            break;
        case _COLEMAK:
            rgb_matrix_layer_helper(HSV_MAGENTA, mode, rgb_matrix_config.speed, type);
            break;
        case _DVORAK:
            rgb_matrix_layer_helper(HSV_SPRINGGREEN, mode, rgb_matrix_config.speed, type);
            break;
        case _WORKMAN:
            rgb_matrix_layer_helper(HSV_GOLDENROD, mode, rgb_matrix_config.speed, type);
            break;
        case _NORMAN:
            rgb_matrix_layer_helper(HSV_CORAL, mode, rgb_matrix_config.speed, type);
            break;
        case _MALTRON:
            rgb_matrix_layer_helper(HSV_YELLOW, mode, rgb_matrix_config.speed, type);
            break;
        case _EUCALYN:
            rgb_matrix_layer_helper(HSV_PINK, mode, rgb_matrix_config.speed, type);
            break;
        case _CARPLAX:
            rgb_matrix_layer_helper(HSV_BLUE, mode, rgb_matrix_config.speed, type);
            break;
    }
}

void rgb_matrix_indicators_user(void) {
    if (userspace_config.rgb_layer_change &&
#    ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        !g_suspend_state &&
#    endif
#    if defined(RGBLIGHT_ENABLE)
        (!rgblight_config.enable && rgb_matrix_config.enable)
#    else
        rgb_matrix_config.enable
#    endif
    ) {
        switch (biton32(layer_state)) {
            case _GAMEPAD:
                rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _DIABLO:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                rgb_matrix_layer_helper(HSV_YELLOW, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_BLUE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                rgb_matrix_layer_helper(HSV_BLUE, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            default: {
                check_default_layer(IS_LAYER_ON(_MODS), LED_FLAG_UNDERGLOW);
                break;
            }
        }
        // check_default_layer(0, LED_FLAG_MODIFIER);
    }
}
#endif
