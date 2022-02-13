/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  // Left
  // 0  1  2  3  4  5
  //                   ROWS
  // 06 05 04 03 02 01   0
  // 07 08 09 10 11 12   1
  // 18 17 16 15 14 13   2
  //
  //          19 20 21   3
  //
  // Right
  // 0  1  2  3  4  5
  //                    ROWS
  // 06 05 04 03 02 01   4
  // 07 08 09 10 11 12   5
  // 18 17 16 15 14 13   6
  //
  //          19 20 21   7
  //
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 06 05 04 03 02 01       01 02 03 04 05 06  0
  // 07 08 09 10 11 12       12 11 10 09 08 07  1
  // 18 17 16 15 14 13       13 14 15 16 17 18  2
  //           19 20 21     21 20 19            3

// First section is the wiring order of LEDs
// Second section is physical x,y coordinates
// Third section is type of LED:
// 1 = modifier key
// 2 = underglow
// 4 = per-key backlight
// 8 = keyboard state indicator
led_config_t g_led_config = { {
    {  6,  5,  4,  3,  2,   1 },
    {  7,  8,  9,  10,  11,   12 },
    {  18,  17,  16,  15,  14,   13 },
    { NO_LED, NO_LED, NO_LED,  19,  20,   21 },
    { 27, 26, 25,  24,  23,  22 },
    {  28,  29,  30,  31,  32,  33 },
    {  39,  38,  37,  36,  35,  34 },
    { NO_LED, NO_LED, NO_LED,  40,  41,  42 }
  }, {
    {  85,   7 }, {  68,   7 }, {  50,   7 }, {  33,   7 }, {  16,   7 }, {   0,   7 },
    {   0,  24 }, {  16,  24 }, {  33,  24 }, {  50,  24 }, {  68,  24 }, {  85,  24 },
    {  85,  39 }, {  68,  39 }, {  50,  39 }, {  33,  39 }, {  16,  39 }, {   0,  39 },
    {  60,  55 }, {  80,  55 }, {  95,  55 },
    { 139,   7 }, { 156,   7 }, { 174,   7 }, { 191,   7 }, { 208,   7 }, { 224,   7 },
    { 224,  24 }, { 208,  24 }, { 191,  24 }, { 174,  24 }, { 156,  24 }, { 139,  24 },
    { 139,  39 }, { 156,  39 }, { 174,  39 }, { 191,  39 }, { 208,  39 }, { 224,  39 }, 
    { 164,  55 }, { 144,  55 }, { 129,  55 }
  }, {
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4
} };

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
