
#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>
#include <stdbool.h>

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

#ifdef __cplusplus
}
#endif

#endif // _BOARD_H_