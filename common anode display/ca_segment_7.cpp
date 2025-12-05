#include "ca_segment_7.h"

// Private Global Variables
// We declare them 'static' so they are invisible to other files.
// This protects them from being accidentally changed by main().
static volatile uint8_t *dataout;
static volatile uint8_t *segment_select;

// --- Initialization Function ---
void commonanode_init(volatile uint8_t *d_out, volatile uint8_t *s_out)
{
  // Save the port addresses to our private global variables
  dataout = d_out;
  segment_select = s_out;

  // Initialize the hardware ports
  init_port(dataout, output);
  init_port(segment_select, output);
}

// --- Display Function ---
void commonanode_display(volatile long number)
{
  volatile long i;
  volatile uint8_t thousand, hundred, one, ten;
  
  // Hex codes for Common Anode (0-9)
  volatile uint8_t display[10] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};
  
  // Digit Extraction
  thousand = number / 1000;
  hundred = (number % 1000) / 100;
  ten = (number % 100) / 10;
  one = number % 10;

  // --- Logic for Leading Zero Suppression ---
  
  // Case 1: 4-Digit Number (e.g., 1000 to 9999)
  if(thousand != 0)
  {
    // Digit 1 (Thousands)
    port_drive_out(segment_select, 0x01);
    port_drive_out(dataout, display[thousand]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff); // Clear to prevent ghosting
    for(i=0; i<10; i++);

    // Digit 2 (Hundreds)
    port_drive_out(segment_select, 0x02);
    port_drive_out(dataout, display[hundred]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);

    // Digit 3 (Tens)
    port_drive_out(segment_select, 0x04);
    port_drive_out(dataout, display[ten]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);

    // Digit 4 (Ones)
    port_drive_out(segment_select, 0x08);
    port_drive_out(dataout, display[one]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);
  }
  
  // Case 2: 3-Digit Number (e.g., 100 to 999)
  else if(hundred != 0)
  {
    // Skip Digit 1
    
    // Digit 2
    port_drive_out(segment_select, 0x02);
    port_drive_out(dataout, display[hundred]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);

    // Digit 3
    port_drive_out(segment_select, 0x04);
    port_drive_out(dataout, display[ten]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);

    // Digit 4
    port_drive_out(segment_select, 0x08);
    port_drive_out(dataout, display[one]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);
  }
  
  // Case 3: 2-Digit Number (e.g., 10 to 99)
  else if(ten != 0)
  {
    // Skip Digit 1 & 2
    
    // Digit 3
    port_drive_out(segment_select, 0x04);
    port_drive_out(dataout, display[ten]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);

    // Digit 4
    port_drive_out(segment_select, 0x08);
    port_drive_out(dataout, display[one]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);
  }
  
  // Case 4: 1-Digit Number (0 to 9)
  else
  {
    // Skip Digit 1, 2, & 3
    
    // Digit 4
    port_drive_out(segment_select, 0x08);
    port_drive_out(dataout, display[one]);
    for(i=0; i<4000; i++);
    port_drive_out(dataout, 0xff);
    for(i=0; i<10; i++);
  }    
}
