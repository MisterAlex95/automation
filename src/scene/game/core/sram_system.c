#include "sram_system.h"

void sram_enable(void) { ENABLE_RAM_MBC1; }

void sram_disable(void) { DISABLE_RAM; }

void sram_write_byte(UINT16 address, UBYTE data) {
  sram_enable();
  *((UBYTE *)(SRAM_START_ADDR + address)) = data;
  sram_disable();
}

UBYTE sram_read_byte(UINT16 address) {
  sram_enable();
  UBYTE data = *((UBYTE *)(SRAM_START_ADDR + address));
  sram_disable();
  return data;
}

void sram_write_block(UINT16 address, UBYTE *data, UINT16 size) {
  sram_enable();
  for (UINT16 i = 0; i < size; i++) {
    *((UBYTE *)(SRAM_START_ADDR + address + i)) = data[i];
  }
  sram_disable();
}

void sram_read_block(UINT16 address, UBYTE *data, UINT16 size) {
  sram_enable();
  for (UINT16 i = 0; i < size; i++) {
    data[i] = *((UBYTE *)(SRAM_START_ADDR + address + i));
  }
  sram_disable();
}