#include "w25q64.h"

static bus_status_t jedec(uint8_t out[3]) {
    uint8_t tx[4] = {W25Q64_CMD_JEDEC, 0, 0, 0};
    uint8_t rx[4] = {0};
    bus->cs_set(1);
    bus_status_t s = bus->spi_transfer(tx, rx, 4);
    bus->cs_set(0);
    if (s != BUS_OK) return s;
    out[0] = rx[1]; out[1] = rx[2]; out[2] = rx[3];
    return BUS_OK;
}

bus_status_t W25Q64_ReadJedec(uint8_t jedec_out[3]) { return jedec(jedec_out); }

bus_status_t W25Q64_WriteByte(uint16_t addr, uint8_t val) {
    uint8_t tx_wren = W25Q64_CMD_WREN, rx_dummy;
    bus->cs_set(1);
    bus_status_t s = bus->spi_transfer(&tx_wren, &rx_dummy, 1);
    bus->cs_set(0);
    if (s != BUS_OK) return s;
    bus->delay_ms(1);

    uint8_t tx[4] = {W25Q64_CMD_PROGRAM, (uint8_t)(addr >> 8), (uint8_t)(addr & 0xFF), val};
    uint8_t rx[4] = {0};
    bus->cs_set(1);
    s = bus->spi_transfer(tx, rx, 4);
    bus->cs_set(0);
    if (s != BUS_OK) return s;
    bus->delay_ms(5);
    return BUS_OK;
}