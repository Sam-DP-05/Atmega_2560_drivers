#include "keypad_4x4.h"

// --- Private Variables ---
// 'static' means these are only visible inside this file
static volatile uint8_t *row_ptr;
static volatile uint8_t *col_ptr;

// --- Initialization ---
void keypad_init(volatile uint8_t *user_row, volatile uint8_t *user_col)
{
  // 1. Save the addresses to our private variables
  row_ptr = user_row;
  col_ptr = user_col;

  // 2. Initialize the ports using your HAL
  init_port(row_ptr, output);
  init_port(col_ptr, input);
}

// --- Scanning Logic ---
volatile uint8_t keypad_number(void)
{
  // Your custom keymap
  const uint8_t keymap[4][4] = {
    {'D','F','0','E'},
    {'C','9','8','7'},
    {'B','6','5','4'},
    {'A','3','2','1'}
  };

  volatile uint8_t col_data;
  volatile uint8_t row_index;
  volatile uint8_t pressed_key = 0; // Initialize to 0

  for (row_index = 0; row_index < 4; row_index++)
  {
    // 1. Drive the Row High
    port_drive_out(row_ptr, (1 << row_index));
    
    // (Recommended: Add a tiny delay here for voltage to settle)
    for(volatile int i=0; i<100; i++); 

    // 2. Read the Columns
    col_data = port_read_in(col_ptr);

    // 3. Check for press
    if (col_data & 0x0F)
    {
       // A. Debounce
       for (volatile long debounce_delay = 0; debounce_delay < 20000; debounce_delay++);
       
       // B. Read Again
       col_data = port_read_in(col_ptr);

       // C. Determine Key
       if(col_data & 0x01) pressed_key = keymap[row_index][0];
       if(col_data & 0x02) pressed_key = keymap[row_index][1];
       if(col_data & 0x04) pressed_key = keymap[row_index][2];
       if(col_data & 0x08) pressed_key = keymap[row_index][3];

       // D. Wait for Release (Blocking)
       // This prevents "11111" when holding the key
       while( (port_read_in(col_ptr) & 0x0F) != 0 );

       return pressed_key;
    }
  }
  
  return 0; // No key pressed
}
