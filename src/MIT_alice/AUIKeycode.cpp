#include "pch.h"
#include "AUIKeycode.h"

#if defined(_WIN32)

#include <winuser.h>

const unsigned int MAUIKeycode::kBackspace = VK_BACK;
const unsigned int MAUIKeycode::kDelete = VK_DELETE;
const unsigned int MAUIKeycode::kArrowUp = VK_UP;
const unsigned int MAUIKeycode::kArrowDown = VK_DOWN;
const unsigned int MAUIKeycode::kArrowLeft = VK_LEFT;
const unsigned int MAUIKeycode::kArrowRight = VK_RIGHT;
const unsigned int MAUIKeycode::kCapslock = VK_CAPITAL;
const unsigned int MAUIKeycode::kContextMenu = VK_APPS;
const unsigned int MAUIKeycode::kBreak = VK_CANCEL;
const unsigned int MAUIKeycode::kHome = VK_HOME;
const unsigned int MAUIKeycode::kEnd = VK_END;
const unsigned int MAUIKeycode::kInsert = VK_INSERT;
const unsigned int MAUIKeycode::kKana = VK_KANA;
const unsigned int MAUIKeycode::kKanji = VK_KANJI;
const unsigned int MAUIKeycode::kJunja = VK_JUNJA;
const unsigned int MAUIKeycode::kHelp = VK_HELP;
const unsigned int MAUIKeycode::kFinal = VK_FINAL;
const unsigned int MAUIKeycode::kLeftControl = VK_LCONTROL;
const unsigned int MAUIKeycode::kLeftAlt = VK_LMENU;
const unsigned int MAUIKeycode::kLeftShift = VK_LSHIFT;
const unsigned int MAUIKeycode::kLeftWin = VK_LWIN;
const unsigned int MAUIKeycode::kRightControl = VK_RCONTROL;
const unsigned int MAUIKeycode::kRightAlt = VK_RMENU;
const unsigned int MAUIKeycode::kRightShift = VK_RSHIFT;
const unsigned int MAUIKeycode::kRightWin = VK_RWIN;
const unsigned int MAUIKeycode::kMouseLeftButton = VK_LBUTTON;
const unsigned int MAUIKeycode::kMouseRightButton = VK_RBUTTON;
const unsigned int MAUIKeycode::kMouseMiddleButton = VK_MBUTTON;
const unsigned int MAUIKeycode::kPrintScreen = VK_SNAPSHOT;
const unsigned int MAUIKeycode::kClear = VK_CLEAR;
const unsigned int MAUIKeycode::kDecimal = VK_DECIMAL;
const unsigned int MAUIKeycode::kDivide = VK_DIVIDE;
const unsigned int MAUIKeycode::kMultiply = VK_MULTIPLY;
const unsigned int MAUIKeycode::kAdd = VK_ADD;
const unsigned int MAUIKeycode::kSubtract = VK_SUBTRACT;
const unsigned int MAUIKeycode::kNumpad_0 = VK_NUMPAD0;
const unsigned int MAUIKeycode::kNumpad_1 = VK_NUMPAD1;
const unsigned int MAUIKeycode::kNumpad_2 = VK_NUMPAD2;
const unsigned int MAUIKeycode::kNumpad_3 = VK_NUMPAD3;
const unsigned int MAUIKeycode::kNumpad_4 = VK_NUMPAD4;
const unsigned int MAUIKeycode::kNumpad_5 = VK_NUMPAD5;
const unsigned int MAUIKeycode::kNumpad_6 = VK_NUMPAD6;
const unsigned int MAUIKeycode::kNumpad_7 = VK_NUMPAD7;
const unsigned int MAUIKeycode::kNumpad_8 = VK_NUMPAD8;
const unsigned int MAUIKeycode::kNumpad_9 = VK_NUMPAD9;
const unsigned int MAUIKeycode::kTab = VK_TAB;
const unsigned int MAUIKeycode::kBackTab = VK_OEM_BACKTAB;
const unsigned int MAUIKeycode::kJump = VK_OEM_JUMP;
const unsigned int MAUIKeycode::kReset = VK_OEM_RESET;
const unsigned int MAUIKeycode::kEnter = VK_RETURN;
const unsigned int MAUIKeycode::kSpace = VK_SPACE;
const unsigned int MAUIKeycode::kEscape = VK_ESCAPE;
const unsigned int MAUIKeycode::kExecute = VK_EXECUTE;
const unsigned int MAUIKeycode::kKey_0 = 0x30;
const unsigned int MAUIKeycode::kKey_1 = 0x31;
const unsigned int MAUIKeycode::kKey_2 = 0x32;
const unsigned int MAUIKeycode::kKey_3 = 0x33;
const unsigned int MAUIKeycode::kKey_4 = 0x34;
const unsigned int MAUIKeycode::kKey_5 = 0x35;
const unsigned int MAUIKeycode::kKey_6 = 0x36;
const unsigned int MAUIKeycode::kKey_7 = 0x37;
const unsigned int MAUIKeycode::kKey_8 = 0x38;
const unsigned int MAUIKeycode::kKey_9 = 0x39;
const unsigned int MAUIKeycode::kKey_A = 0x41;
const unsigned int MAUIKeycode::kKey_B = 0x42;
const unsigned int MAUIKeycode::kKey_C = 0x43;
const unsigned int MAUIKeycode::kKey_D = 0x44;
const unsigned int MAUIKeycode::kKey_E = 0x45;
const unsigned int MAUIKeycode::kKey_F = 0x46;
const unsigned int MAUIKeycode::kKey_G = 0x47;
const unsigned int MAUIKeycode::kKey_H = 0x48;
const unsigned int MAUIKeycode::kKey_I = 0x49;
const unsigned int MAUIKeycode::kKey_J = 0x4A;
const unsigned int MAUIKeycode::kKey_K = 0x4B;
const unsigned int MAUIKeycode::kKey_L = 0x4C;
const unsigned int MAUIKeycode::kKey_M = 0x4D;
const unsigned int MAUIKeycode::kKey_N = 0x4E;
const unsigned int MAUIKeycode::kKey_O = 0x4F;
const unsigned int MAUIKeycode::kKey_P = 0x50;
const unsigned int MAUIKeycode::kKey_Q = 0x51;
const unsigned int MAUIKeycode::kKey_R = 0x52;
const unsigned int MAUIKeycode::kKey_S = 0x53;
const unsigned int MAUIKeycode::kKey_T = 0x54;
const unsigned int MAUIKeycode::kKey_U = 0x55;
const unsigned int MAUIKeycode::kKey_V = 0x56;
const unsigned int MAUIKeycode::kKey_W = 0x57;
const unsigned int MAUIKeycode::kKey_X = 0x58;
const unsigned int MAUIKeycode::kKey_Y = 0x59;
const unsigned int MAUIKeycode::kKey_Z = 0x5A;
const unsigned int MAUIKeycode::kF1 = VK_F1;
const unsigned int MAUIKeycode::kF2 = VK_F2;
const unsigned int MAUIKeycode::kF3 = VK_F3;
const unsigned int MAUIKeycode::kF4 = VK_F4;
const unsigned int MAUIKeycode::kF5 = VK_F5;
const unsigned int MAUIKeycode::kF6 = VK_F6;
const unsigned int MAUIKeycode::kF7 = VK_F7;
const unsigned int MAUIKeycode::kF8 = VK_F8;
const unsigned int MAUIKeycode::kF9 = VK_F9;
const unsigned int MAUIKeycode::kF10 = VK_F10;
const unsigned int MAUIKeycode::kF11 = VK_F11;
const unsigned int MAUIKeycode::kF12 = VK_F12;
const unsigned int MAUIKeycode::kF13 = VK_F13;
const unsigned int MAUIKeycode::kF14 = VK_F14;
const unsigned int MAUIKeycode::kF15 = VK_F15;
const unsigned int MAUIKeycode::kF16 = VK_F16;
const unsigned int MAUIKeycode::kF17 = VK_F17;
const unsigned int MAUIKeycode::kF18 = VK_F18;
const unsigned int MAUIKeycode::kF19 = VK_F19;
const unsigned int MAUIKeycode::kF20 = VK_F20;
const unsigned int MAUIKeycode::kF21 = VK_F21;
const unsigned int MAUIKeycode::kF22 = VK_F22;
const unsigned int MAUIKeycode::kF23 = VK_F23;
const unsigned int MAUIKeycode::kF24 = VK_F24;

#else

#   error TODO: Implement for other OS

#endif
