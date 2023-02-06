#ifndef keycode_hpp
#define keycode_hpp

// PURPOSE : Defines macros for key inputs.

//Pragma
#pragma once

//Action
#define Release 0
#define Press 1
#define Hold 2

//Mouse buttons
#define leftClick 0
#define rightClick 1
#define middleMouseButton 2
#define mButton4 3
#define mButton5 4
#define mButton6 5
#define mButton7 6
#define mButton8 7

#define mButtonLast GLFW_MOUSE_BUTTON_8
#define mButtonLeft GLFW_MOUSE_BUTTON_1
#define mButtonRight GLFW_MOUSE_BUTTON_2
#define mButtonMiddle GLFW_MOUSE_BUTTON_3

//Keyboard keys
#define     Unknown   -1
#define     Space   32
#define     Apostrophe   39 /* ' */
#define     Comma   44 /* , */
#define     Minus   45 /* - */
#define     Period   46 /* . */
#define     Slash   47 /* / */

#define     Key0   48
#define     Key1   49
#define     Key2   50
#define     Key3   51
#define     Key4   52
#define     Key5   53
#define     Key6   54
#define     Key7   55
#define     Key8   56
#define     Key9   57

#define     Semicolon   59 /* ; */
#define     Equal   61 /* = */

#define     A   65
#define     B   66
#define     C   67
#define     D   68
#define     E   69
#define     F   70
#define     G   71
#define     H   72
#define     I   73
#define     J   74
#define     K   75
#define     L   76
#define     M   77
#define     N   78
#define     O   79
#define     P   80
#define     Q   81
#define     R   82
#define     S   83
#define     T   84
#define     U   85
#define     V   86
#define     W   87
#define     X   88
#define     Y   89
#define     Z   90

#define     lBracket   91 /* [ */
#define     bSlash   92 /* \ */
#define     rBracket   93 /* ] */
#define     Accent   96 /* ` */
#define     world1   161 /* non-US #1 */
#define     world2   162 /* non-US #2 */
#define     Escape   256
#define     Enter   257
#define     Tab   258
#define     Backspace   259
#define     Insert   260
#define     Delete   261

#define     Right   262
#define     Left   263
#define     Down   264
#define     Up   265

#define     pUp   266
#define     pDown   267
#define     Home   268
#define     End   269
#define     capsLock   280
#define     scrollLock   281
#define     numLock   282
#define     printScreen   283
#define     Pause   284

#define     F1    290
#define     F2   291
#define     F3   292
#define     F4   293
#define     F5   294
#define     F6   295
#define     F7   296
#define     F8   297
#define     F9   298
#define     F10   299
#define     F11   300
#define     F12   301
#define     F13   302
#define     F14   303
#define     F15   304
#define     F16   305
#define     F17   306
#define     F18   307
#define     F19   308
#define     F20   309
#define     F21   310
#define     F22   311
#define     F23   312
#define     F24   313
#define     F25   314

#define     Num0   320
#define     Num1   321
#define     Num2   322
#define     Num3   323
#define     Num4   324
#define     Num5   325
#define     Num6   326
#define     Num7   327
#define     Num8   328
#define     Num9   329
#define     Decimal   330
#define     Divide   331
#define     Multiply   332
#define     Subtract   333
#define     Add   334
#define     NumEnter   335
#define     NumEqual   336

#define     lShift   340
#define     lControl   341
#define     lAlt   342
#define     lSuper   343
#define     rShift   344
#define     rControl   345
#define     rAlt   346
#define     rSuper   347
#define     Menu   348
#define     Last   Menu

//Macro modifier keys
#define modShift 0x0001
#define modControl 0x0002
#define modAlt 0x0004
#define modSuper 0x0008

#endif /* keycode_hpp */
