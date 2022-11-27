
#ifndef _SPI_BOARD_H_
#define _SPI_BOARD_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "ldl_chip.h"

#ifdef __cplusplus
extern "C" {
#endif

    void spiInit(void);
    
    uint8_t spiTransfer(uint8_t byte);

#ifdef __cplusplus
}
#endif

#endif // _SPI_BOARD_H_
