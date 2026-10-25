#include <assert.h>
#include <stdio.h>
#include "w25q64.h"

int main(void) {
    fake_reset();
    assert(W25Q64_WriteByte(0x0100, 0xAB) == BUS_OK);

    /* має бути щонайменше 2 SPI-транзакції: WREN, PROGRAM */
    assert(fake_get_spi_txn_count() >= 2);
    uint8_t *tx0 = fake_get_spi_txn(0);
    uint8_t *tx1 = fake_get_spi_txn(1);
    assert(tx0[0] == W25Q64_CMD_WREN);          /* перша - WREN */
    assert(tx1[0] == W25Q64_CMD_PROGRAM);       /* друга - PROGRAM */
    assert(tx1[1] == 0x01 && tx1[2] == 0x00);   /* адреса */
    assert(tx1[3] == 0xAB);                     /* дані */

    printf("test_w25q64: WREN->PROGRAM sequence PASS\n");
    return 0;
}