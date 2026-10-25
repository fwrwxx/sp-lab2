#include "bus.h"
#include <string.h>

static bus_status_t fake_i2c_write(uint8_t addr, const uint8_t *data, size_t len) {
    return BUS_OK;
}

static bus_status_t fake_i2c_read(uint8_t addr, uint8_t *data, size_t len) {
    if (len == 1) data[0] = 0x68;
    if (len == 2) { data[0] = 0x00; data[1] = 0x40; } // AccelX = 64
    return BUS_OK;
}

static bus_status_t fake_spi_transfer(const uint8_t *tx, uint8_t *rx, size_t len) {
    return BUS_OK;
}

static const bus_t fake_bus = {
    .i2c_write = fake_i2c_write,
    .i2c_read = fake_i2c_read,
    .spi_transfer = fake_spi_transfer
};

const bus_t *bus = &fake_bus;