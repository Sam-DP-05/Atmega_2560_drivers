#ifndef HAL_H
#define HAL_H

#include <stdint.h> 

// --- Register Definitions (Based on DDR Addresses) ---
#define PORT_A ((volatile uint8_t*)0x21)
#define PORT_B ((volatile uint8_t*)0x24)
#define PORT_C ((volatile uint8_t*)0x27)
#define PORT_D ((volatile uint8_t*)0x2A)
#define PORT_E ((volatile uint8_t*)0x2D)
#define PORT_F ((volatile uint8_t*)0x30)
#define PORT_G ((volatile uint8_t*)0x33)

// Extended Ports (ATmega2560 specific)
#define PORT_H ((volatile uint8_t*)0x101)
#define PORT_J ((volatile uint8_t*)0x104)
#define PORT_K ((volatile uint8_t*)0x107)
#define PORT_L ((volatile uint8_t*)0x10A)

// --- Type Definitions ---
typedef enum{
  input = 0,
  output = 1
} drivemode;

// --- Function Prototypes (Declarations Only) ---
void init_port(volatile uint8_t *port, drivemode mode);
void port_drive_out(volatile uint8_t *port, uint8_t user_data);
uint8_t port_read_in(volatile uint8_t *port);

#endif
