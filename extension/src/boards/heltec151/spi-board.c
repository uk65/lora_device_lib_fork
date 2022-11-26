
#include "spi-board.h"

void chip_set_mode(void *self, enum ldl_chip_mode mode)
{
}

bool chip_write(void *self, const void *opcode, size_t opcode_size, const void *data, size_t size)
{
    return true;
}

bool chip_read(void *self, const void *opcode, size_t opcode_size, void *data, size_t size)
{
    return true;
}


