#include "hal.h"

// Initialize Direction Register (DDR)
// Logic: Directly writes to the address defined in macros (0x21, etc.)
void init_port(volatile uint8_t *port, drivemode mode)
{
  if(mode == output)
  {
    *port = 0xff; // Set all pins to OUTPUT
  }
  else
  {
    *port = 0x00; // Set all pins to INPUT
  }
}

// Write to Output Register (PORT)
// Logic: DDR address + 1 = PORT address (e.g., 0x21 + 1 = 0x22)
void port_drive_out(volatile uint8_t *port, uint8_t user_data)
{
  port++;         // Increment pointer to reach PORT register
  *port = user_data;
}

// Read from Input Register (PIN)
// Logic: DDR address - 1 = PIN address (e.g., 0x21 - 1 = 0x20)
uint8_t port_read_in(volatile uint8_t *port)
{
  port--;         // Decrement pointer to reach PIN register
  uint8_t userdata;
  userdata = *port;
  return userdata;
}
