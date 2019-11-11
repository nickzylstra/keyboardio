// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

// graphic for layout
// http://www.keyboard-layout-editor.com/#/gists/a0fd4537e2cc0aeaaed49496837a8796

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
   These #include directives pull in the Kaleidoscope firmware core,
   as well as the Kaleidoscope plugins we use in the Model 01's firmware
*/


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rai nbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-Colormap.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Support for produce one keycode (i.e. symbol) when tapped, and a different keycode when held.
#include "Kaleidoscope-Qukeys.h"

// Support for oneshot keys
#include "Kaleidoscope-Oneshot.h"

// Support for modifier led activation
#include "Kaleidoscope-LED-ActiveModColor.h"

// Support for tapdance keys
// #include "Kaleidoscope-TapDance.h"

/** This 'enum' is a list of all the macros used by the Model 01's firmware
    The names aren't particularly important. What is important is that each
    is unique.

    These are the names of your macros. They'll be used in two places.
    The first is in your keymap definitions. There, you'll use the syntax
    `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`

    The second usage is in the 'switch' statement in the `macroAction` function.
    That switch statement actually runs the code associated with a macro when
    a macro key is pressed.
*/

enum { MACRO_VERSION_INFO,
       MACRO_ANY,
       MACRO_CUTLINE,
       MACRO_VIMSAVEQUIT,
       MACRO_SELECTCURWORD,
       MACRO_TRIPEQ
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
    keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
    keymap.

    Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
    of first the left hand's layout, followed by the right hand's layout.

    Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
    defined as part of the USB HID Keyboard specification. You can find the names
    (if not yet the explanations) for all the standard `Key_` defintions offered by
    Kaleidoscope in these files:
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h

    Additional things that should be documented here include
      using ___ to let keypresses fall through to the previously active layer
      using XXX to mark a keyswitch as 'blocked' on this layer
      using ShiftToLayer() and LockLayer() keys to change the active keymap.
      keeping NUM and FN consistent and accessible on all layers

    The PROG key is special, since it is how you indicate to the board that you
    want to flash the firmware. However, it can be remapped to a regular key.
    When the keyboard boots, it first looks to see whether the PROG key is held
    down; if it is, it simply awaits further flashing instructions. If it is
    not, it continues loading the rest of the firmware and the keyboard
    functions normally, with whatever binding you have set to PROG. More detail
    here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8

    The "keymaps" data structure is a list of the keymaps compiled into the firmware.
    The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
    macros switch to key layers based on this list.



    A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
    Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
*/

/**
    Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
    The third one is layer 2.
    This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
    the numbers 0, 1 and 2.

*/

enum { PRIMARY, FUNC, NUMPAD, PUNC, QWERTY }; // layers


/**
    To change your keyboard's layout from QWERTY to DVORAK or COLEMAK, comment out the line

    #define PRIMARY_KEYMAP_QWERTY

    by changing it to

    // #define PRIMARY_KEYMAP_QWERTY

    Then uncomment the line corresponding to the layout you want to use.

*/

// #define PRIMARY_KEYMAP_QWERTY
// #define PRIMARY_KEYMAP_COLEMAK
// #define PRIMARY_KEYMAP_DVORAK
#define PRIMARY_KEYMAP_MTGAP



/* This comment temporarily turns off astyle's indent enforcement
     so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*

KEYMAPS(

#if defined (PRIMARY_KEYMAP_QWERTY)
  [PRIMARY] = KEYMAP_STACKED
  (___,           Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick,  Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,    Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown,  Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftShift, Key_Spacebar, Key_LeftGui, Key_LeftControl,
   ShiftToLayer(FUNC),

   LockLayer(MTGAP),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,         Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                      Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_LeftGui,       Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightControl,  Key_LeftGui, Key_Backspace, Key_RightShift,
   ShiftToLayer(FUNC)),

#elif defined (PRIMARY_KEYMAP_DVORAK)

  [PRIMARY] = KEYMAP_STACKED
  (___,          Key_1,         Key_2,     Key_3,      Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, Key_Tab,
   Key_PageUp,   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
   Key_PageDown, Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),   Key_6, Key_7, Key_8, Key_9, Key_0, LockLayer(NUMPAD),
   Key_Enter,      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   Key_RightAlt,   Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

#elif defined (PRIMARY_KEYMAP_COLEMAK)

  [PRIMARY] = KEYMAP_STACKED
  (___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_F, Key_P, Key_G, Key_Tab,
   Key_PageUp,   Key_A, Key_R, Key_S, Key_T, Key_D,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,     Key_J, Key_L, Key_U,     Key_Y,         Key_Semicolon, Key_Equals,
                  Key_H, Key_N, Key_E,     Key_I,         Key_O,         Key_Quote,
   Key_RightAlt,  Key_K, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

#elif defined (PRIMARY_KEYMAP_MTGAP)
  [PRIMARY] = KEYMAP_STACKED
  (Key_Escape,     Key_1,              Key_2,            Key_3,            Key_4,          Key_5, LGUI(Key_Backtick),
   Key_Backtick,   Key_W,              Key_C,            Key_L,            Key_D,          Key_K, Key_Tab,
   Key_PageUp,     MT(LeftAlt, R),     MT(LeftShift, S), MT(LeftGui, T),   LT(PUNC, H),    Key_M,
   Key_PageDown,   Key_X,              Key_V,            Key_G,            Key_F,          Key_B, LALT(LGUI(Key_LeftArrow)),
   OSM(LeftControl), Key_Spacebar, OSM(LeftShift), OSM(LeftGui), 
   ShiftToLayer(FUNC),
   Key_UpArrow,           Key_6,              Key_7,             Key_8,             Key_9,              Key_0,                LockLayer(NUMPAD),
   Key_Enter,             Key_J,              Key_U,             Key_O,             Key_P,              Key_Y,                Key_Equals,
                          Key_Comma,          LT(PUNC, A),       MT(RightGui, E),   MT(RightShift, N),  MT(RightAlt, I),      Key_Semicolon,
   Key_DownArrow,         LSHIFT(Key_Slash),  Key_Period,        Key_Quote,         Key_Z,              Key_Q,                Key_Minus,
   OSM(LeftAlt), OSM(RightShift), Key_Backspace, Key_Delete,
   ShiftToLayer(FUNC)),

#else

#error "No default keymap defined. You should make sure that you have a line like '#define PRIMARY_KEYMAP_QWERTY' in your sketch"

#endif


  [FUNC] =  KEYMAP_STACKED
  (___,                        Key_F1,                    Key_F2,            Key_F3,            Key_F4,             Key_F5,           ___,
   Consumer_PlaySlashPause,    Consumer_Mute,             Key_mouseScrollR,  Key_mouseUp,       Key_mouseScrollL,   Key_mouseWarpEnd, Key_mouseWarpNE,
   Consumer_ScanNextTrack,     Consumer_VolumeIncrement,  Key_mouseL,        Key_mouseDn,       Key_mouseR,         Key_mouseWarpNW,
   Consumer_ScanPreviousTrack, Consumer_VolumeDecrement,  ___,               Key_mouseScrollDn, Key_mouseScrollUp,  Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, ___, ___, ___,
   ___,

   Key_mouseBtnR,     Key_F6,                       Key_F7,               Key_F8,               Key_F9,                       Key_F10,    Key_F11,
   ___,               Key_mouseBtnL,                LALT(Key_LeftArrow),  LALT(Key_RightArrow), M(MACRO_SELECTCURWORD),       ___,        Key_F12,
                      Key_LeftArrow,                Key_DownArrow,        Key_UpArrow,          Key_RightArrow,               ___,        ___,
   ___,               LSHIFT(LALT(Key_LeftArrow)),  Key_Home,             Key_End,              LSHIFT(LALT(Key_RightArrow)), ___,        ___,
   ___, ___, ___, ___,
   ___),

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___,                Key_7, Key_8,      Key_9,                  Key_KeypadDivide,   ___,
   ___,                    ___,                Key_4, Key_5,      Key_6,                  Key_KeypadMultiply, ___,
                           Key_Backspace,      Key_1, Key_2,      Key_3,                  Key_KeypadAdd,      ___,
   ___,                    ___,                Key_0, Key_Period, Key_Equals,             Key_KeypadSubtract, Key_Enter,
   ___, ___, ___, ___,        
   ___),

  [PUNC] =  KEYMAP_STACKED
  (___, ___,           ___,           ___,                     ___,                      ___,           ___,
   ___, LSHIFT(Key_2), LSHIFT(Key_3), LSHIFT(Key_LeftBracket), LSHIFT(Key_RightBracket), LSHIFT(Key_6), ___,
   ___, LSHIFT(Key_7), Key_Pipe,      LSHIFT(Key_9),           LSHIFT(Key_0),            LSHIFT(Key_1),
   ___, LSHIFT(Key_4), LSHIFT(Key_5), Key_LeftBracket,         Key_RightBracket,         Key_Backslash, ___,
   ___, ___, ___, ___,
   ___,

   ___, ___,                   ___,                ___,                ___,                ___,           ___,
   ___, LSHIFT(Key_Backtick),  Key_Backtick,       LSHIFT(Key_8),      LSHIFT(Key_Equals), ___,           ___,
        LSHIFT(Key_Semicolon), Key_Equals,         Key_Slash,          Key_Minus,          Key_Semicolon, ___,
   ___, ___,                   LSHIFT(Key_Comma),  LSHIFT(Key_Period), LSHIFT(Key_Minus),  ___,           ___,
   ___, ___, ___, ___,
   ___),

  [QWERTY] = KEYMAP_STACKED
  (___,          Key_1, Key_2, Key_3, Key_4, Key_5, ___,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, ___,
   ___,          Key_A, Key_S, Key_D, Key_F, Key_G,
   ___,          Key_Z, Key_X, Key_C, Key_V, Key_B, ___,
   ___, ___, ___, ___,
   ___,

   ___,   Key_6, Key_7, Key_8,     Key_9,         Key_0,         ___,
   ___,   Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
          Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   ___,   Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   ___, ___, ___, ___,
   ___)
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
    When a key bound to the macro is pressed, this macro
    prints out the firmware build information as virtual keystrokes
*/

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.

   When the 'any key' macro is toggled on, a random alphanumeric key is
   selected. While the key is held, the function generates a synthetic
   keypress event repeating that randomly selected key.

*/

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  bool toggledOn = false;
  if (keyToggledOn(keyState)) {
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);
    toggledOn = true;
  }

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey, toggledOn);
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

*/

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

    case MACRO_VERSION_INFO:
      versionInfoMacro(keyState);
      break;

    case MACRO_ANY:
      anyKeyMacro(keyState);
      break;

    case MACRO_CUTLINE:
      return MACRODOWN(D(LeftGui), T(LeftArrow), 
                       D(LeftShift), T(RightArrow),
                       U(LeftShift),
                       T(X),
                       U(LeftGui));
                       
    case MACRO_VIMSAVEQUIT:
      return MACRODOWN(D(LeftShift), T(Semicolon), 
                       U(LeftShift),
                       T(W),
                       T(Q));

    case MACRO_SELECTCURWORD:
      return MACRODOWN(D(LeftAlt), T(LeftArrow), 
                       D(LeftShift), T(RightArrow),
                       U(LeftShift), U(LeftAlt));

    case MACRO_TRIPEQ:
      return MACRODOWN(T(Equals), T(Equals), T(Equals));
  }
  return MACRO_NONE;
}

// tapdance setup for two keys
/** void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
  case 0:
    return tapDanceActionKeys(tap_count, tap_dance_action,
                              Key_PageUp, Key_UpArrow);
  case 1:
    return tapDanceActionKeys(tap_count, tap_dance_action,
                              Key_PageDown, Key_DownArrow);
  }
  }*/

// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
   and turns them back on when it wakes up.
*/
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
    case kaleidoscope::plugin::HostPowerManagement::Suspend:
      LEDControl.set_all_leds_to({0, 0, 0});
      LEDControl.syncLeds();
      LEDControl.paused = true;
      break;
    case kaleidoscope::plugin::HostPowerManagement::Resume:
      LEDControl.paused = false;
      LEDControl.refreshAll();
      break;
    case kaleidoscope::plugin::HostPowerManagement::Sleep:
      break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
   resume, and sleep) to other functions that perform action based on these
   events.
*/
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** A tiny wrapper, to be used by MagicCombo.
   This simply toggles the keyboard protocol via USBQuirks, and wraps it within
   a function with an unused argument, to match what MagicCombo expects.
*/
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
   recognise.
*/
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = { R3C6, R2C6, R3C7 }
                 });

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // This plugin allows you to overload keys on your keyboard so that they
  // produce one keycode (i.e. symbol) when tapped, and a different keycode --
  // most likely a modifier (e.g. shift or alt) -- when held.
  Qukeys,

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  // AlphaSquareEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  NumPad,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  // MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // oneshot modifiers
  OneShot,

  // colored modifiers
  ActiveModColorEffect

  // tapdance keys
  // TapDance
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
   It's called when your keyboard first powers up. This is where you set up
   Kaleidoscope and any plugins.
*/
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = CRGB(255, 0, 0);

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/doc/plugin/LED-Stalker.md
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  EEPROMKeymap.setup(5);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to five layers, which is how
  // many editable layers we have (see above).
  ColormapEffect.max_layers(5);

  // Speed up mouse movement
  MouseKeys.speed = 12;
  MouseKeys.speedDelay = 1;
  MouseKeys.accelSpeed = 4;
  MouseKeys.accelDelay = 64;
  MouseKeys.setSpeedLimit(150);

  // Qukeys setup
  QUKEYS(
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 1), Key_LeftControl),           // homerowL4
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 2), Key_LeftShift),             // homerowL3
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 3), ShiftToLayer(NAV)),         // homerowL2
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 4), Key_LeftAlt),               // homerowL1
    // kaleidoscope::plugin::Qukey(0, KeyAddr(0, 7), Key_LeftGui),               // homerowLThumb1
    // kaleidoscope::plugin::Qukey(0, KeyAddr(1, 7), Key_LeftGui),               // homerowLThumb2
    // kaleidoscope::plugin::Qukey(0, KeyAddr(1, 8), Key_LeftGui),               // homaerowRThumb2
    // kaleidoscope::plugin::Qukey(0, KeyAddr(0, 8), Key_LeftGui),               // homerowRThumb1
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 11), ShiftToLayer(PUNC)),       // homerowR1
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 12), ShiftToLayer(MOUSE)),      // homerowR2
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 13), Key_RightShift),           // homerowR3
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 14), Key_RightControl)          // homerowR4
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 6), Key_LEDEffectNext),            // led 
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 6), LGUI(Key_Tab)),                // tab
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 15), M(MACRO_VIMSAVEQUIT)),        // ;
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 14), Key_RightControl),            // q
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 1), Key_LeftControl),              // x
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 15), Key_RightShift),              // minus
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 15), M(MACRO_TRIPEQ)),             // =
    kaleidoscope::plugin::Qukey(0, KeyAddr(2, 6), LALT(LGUI(Key_RightArrow))),   // esc
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 15), LockLayer(QWERTY)),           // num
    // kaleidoscope::plugin::Qukey(0, KeyAddr(3, 1), LGUI(Key_Z)),                  // x
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 2), LGUI(Key_X)),                  // v
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 3), LGUI(Key_C)),                  // g
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 4), LGUI(Key_V)),                  // f
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 5), M(MACRO_CUTLINE)),             // b
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 1), LGUI(Key_Q)),                  // 1
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 2), LALT(LSHIFT(LGUI(Key_2)))),    // 2
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 3), LALT(LSHIFT(LGUI(Key_3)))),    // 3
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 4), LALT(LSHIFT(LGUI(Key_4)))),    // 4
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 4), LGUI(Key_W)),                  // d
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 3), LGUI(Key_T)),                  // l
    kaleidoscope::plugin::Qukey(0, KeyAddr(1, 0), LGUI(Key_LeftArrow)),          // backtick
    kaleidoscope::plugin::Qukey(0, KeyAddr(0, 5), LCTRL(LSHIFT(LGUI(Key_4)))),   // 5
    // kaleidoscope::plugin::Qukey(0, KeyAddr(0, 6), LGUI(Key_H)),                  // led
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 9), LCTRL(Key_UpArrow)),           // butterfly
    // kaleidoscope::plugin::Qukey(0, KeyAddr(1, 9), Key_UpArrow),                  // enter
    // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 0), Key_UpArrow),                  // pgup
    // kaleidoscope::plugin::Qukey(0, KeyAddr(3, 10), Key_Delete),                  // n
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 0), Key_LeftShift)                    // pgdn
  )

  // Qukeys.setHoldTimeout(250);
  Qukeys.setOverlapThreshold(95);

  // set mod highlighting color
  ActiveModColorEffect.highlight_color = CRGB(0x00, 0xff, 0xff);
}

/** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.

    For Kaleidoscope-based keyboard firmware, you usually just want to
    call Kaleidoscope.loop(); and not do anything custom here.
*/

void loop() {
  Kaleidoscope.loop();
}
