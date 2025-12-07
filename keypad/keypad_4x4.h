#ifndef KEYPAD_4X4_H
#define KEYPAD_4X4_H

#include "hal.h"

// --- Function Prototypes ---
// (Notice the * asterisks. These functions need addresses.)
void keypad_init(volatile uint8_t *user_row, volatile uint8_t *user_col);
volatile uint8_t keypad_number(void);

#endif
