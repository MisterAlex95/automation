#ifndef SRAM_SYSTEM_H
#define SRAM_SYSTEM_H

#include "../../../constants.h"
#include <gb/gb.h>
#include <gb/hardware.h>

// SRAM read/write functions
void sram_write_byte(UINT16 address, UBYTE data);
UBYTE sram_read_byte(UINT16 address);
void sram_write_block(UINT16 address, UBYTE *data, UINT16 size);
void sram_read_block(UINT16 address, UBYTE *data, UINT16 size);

#endif // SRAM_SYSTEM_H