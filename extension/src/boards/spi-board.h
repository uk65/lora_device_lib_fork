
#ifndef _SPI_BOARD_H_
#define _SPI_BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "ldl_chip.h"

void chip_set_mode(void *self, enum ldl_chip_mode mode);
bool chip_write(void *self, const void *opcode, size_t opcode_size, const void *data, size_t size);
bool chip_read(void *self, const void *opcode, size_t opcode_size, void *data, size_t size);


#ifdef __cplusplus
}
#endif

#endif // _SPI_BOARD_H_
