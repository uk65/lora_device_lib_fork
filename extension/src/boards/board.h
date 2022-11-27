
#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "ldl_chip.h"


#ifdef __cplusplus
extern "C" {
#endif

    void initBoard(void);
    
    /* somehow set a timer event that will ensure a wakeup so many ticks in future */
    void wakeup_after(uint32_t ticks);

    /* somehow activate sleep mode */
    void sleep(void);

    /* somehow enable interrupts */
    void enable_interrupts(void);
    
    void chip_set_mode(void *self, enum ldl_chip_mode mode);

    bool chip_write(void *self, const void *opcode, size_t opcode_size, const void *data, size_t size);

    bool chip_read(void *self, const void *opcode, size_t opcode_size, void *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_