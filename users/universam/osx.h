#ifndef KEYMAP_GERMAN_OSX_SL
#define KEYMAP_GERMAN_OSX_SL

#include "keymap.h"

// Alt gr

// normal characters
#define DEX_Z KC_Y
#define DEX_Y KC_Z

#define DEX_A KC_A
#define DEX_B KC_B
#define DEX_C KC_C
#define DEX_D KC_D
#define DEX_E KC_E
#define DEX_F KC_F
#define DEX_G KC_G
#define DEX_H KC_H
#define DEX_I KC_I
#define DEX_J KC_J
#define DEX_K KC_K
#define DEX_L KC_L
#define DEX_M KC_M
#define DEX_N KC_N
#define DEX_O KC_O
#define DEX_P KC_P
#define DEX_Q KC_Q
#define DEX_R KC_R
#define DEX_S KC_S
#define DEX_T KC_T
#define DEX_U KC_U
#define DEX_V KC_V
#define DEX_W KC_W
#define DEX_X KC_X

#define DEX_0 KC_0
#define DEX_1 KC_1
#define DEX_2 KC_2
#define DEX_3 KC_3
#define DEX_4 KC_4
#define DEX_5 KC_5
#define DEX_6 KC_6
#define DEX_7 KC_7
#define DEX_8 KC_8
#define DEX_9 KC_9

#define DEX_DOT KC_DOT
#define DEX_COMM KC_COMM

#define DEX_SS KC_MINS
#define DEX_AE KC_QUOT
#define DEX_UE KC_LBRC
#define DEX_OE KC_SCLN

#define DEX_CIRC KC_NUBS  // accent circumflex ^ and ring °
#define DEX_ACUT KC_EQL   // accent acute ´ and grave `
#define DEX_PLUS KC_RBRC  // + and * and ~
#define DEX_HASH KC_BSLS  // # and '
#define DEX_LESS KC_GRV   // < and > and |
#define DEX_MINS KC_SLSH  // - and _

// shifted characters
#define DEX_RING LSFT(DEX_CIRC)  // °
#define DEX_EXLM LSFT(KC_1)         // !
#define DEX_DQOT LSFT(KC_2)         // "
#define DEX_PARA LSFT(KC_3)         // §
#define DEX_DLR LSFT(KC_4)          // $
#define DEX_PERC LSFT(KC_5)         // %
#define DEX_AMPR LSFT(KC_6)         // &
#define DEX_SLSH LSFT(KC_7)         // /
#define DEX_LPRN LSFT(KC_8)         // (
#define DEX_RPRN LSFT(KC_9)         // )
#define DEX_EQL LSFT(KC_0)          // =
#define DEX_QST LSFT(DEX_SS)     // ?
#define DEX_GRV LSFT(DEX_ACUT)   // `
#define DEX_ASTR LSFT(DEX_PLUS)  // *
#define DEX_QUOT LSFT(DEX_HASH)  // '
#define DEX_MORE LSFT(DEX_LESS)  // >
#define DEX_COLN LSFT(KC_DOT)       // :
#define DEX_SCLN LSFT(KC_COMM)      // ;
#define DEX_UNDS LSFT(DEX_MINS)  // _

// Alt-ed characters
#define DEX_SQ2 LALT(KC_2) // ²
#define DEX_SQ3 LALT(KC_3) // ³
#define DEX_LCBR LALT(KC_8)        // {
#define DEX_LBRC LALT(KC_5)        // [
#define DEX_RBRC LALT(KC_6)        // ]
#define DEX_RCBR LALT(KC_9)        // }
#define DEX_BSLS LALT(LSFT(KC_7))  // backslash
#define DEX_AT LALT(DEX_L)      // @
#define DEX_EURO LALT(KC_E)        // €
#define DEX_TILD LALT(DEX_N)    // ~
#define DEX_PIPE LALT(DEX_7)    // |

#endif
