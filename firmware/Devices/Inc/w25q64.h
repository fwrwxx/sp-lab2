#ifndef W25Q64_H
#define W25Q64_H
#include "bus.h"
#include <stdint.h>

#define W25Q64_CMD_WREN   0x06
#define W25Q64_CMD_PROGRAM 0x02
#define W25Q64_CMD_READ   0x03
#define W25Q64_CMD_JEDEC  0x9F

bus_status_t W25Q64_ReadJedec(uint8_t jedec[3]);
bus_status_t W25Q64_WriteByte(uint16_t addr, uint8_t val);
#endif