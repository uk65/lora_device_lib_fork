
#include <stdlib.h>
#include <string.h>
#include "ldl_radio.h"
#include "ldl_mac.h"
#include "ldl_sm.h"
#include "ldl_system.h"
#include "ldl_region.h"
#include "board.h"
#include "spi-board.h"
#include "config.h"

struct ldl_radio radio;
struct ldl_mac mac;
struct ldl_sm sm;

// pointers to 16B root key
extern const uint8_t app_key[16];

// pointers to 8B identifiers
extern const uint8_t dev_eui[8];
extern const uint8_t join_eui[8];

// a pointer to be passed back to the application (anything you like)
void *app_pointer;

// a pointer to be passed to the chip interface (anything you like)
void *chip_interface_pointer;

// Called from within LDL_MAC_process() to pass events back to the application
void app_handler(void *app, enum ldl_mac_response_type type, const union ldl_mac_response_arg *arg);

uint32_t system_ticks(void *app);
long unsigned int system_rand(void *app);


int main(void)
{
    // initialise the default security module
    LDL_SM_init(&sm, app_key);

    {
        // setup the radio
        struct ldl_sx127x_init_arg arg = {
            .xtal          = LDL_RADIO_XTAL_CRYSTAL,
            .tx_gain       = 200,  /* 2dBi */
            .chip          = chip_interface_pointer,
            .chip_write    = chip_write,
            .chip_read     = chip_read,
            .chip_set_mode = chip_set_mode,
            .pa            = LDL_SX127X_PA_RFO,
        };
        LDL_SX1276_init(&radio, &arg);
    }

    {
        struct ldl_mac_init_arg arg = {
            .app               = app_pointer,
            .radio             = &radio,
            .radio_interface   = LDL_Radio_getInterface(&radio),
            .sm                = &sm,
            .sm_interface      = LDL_SM_getInterface(),
            .handler           = app_handler,
            .session           = NULL,            // restore cached session state (or not, in this case)
            .joinEUI           = join_eui,
            .devEUI            = dev_eui,
            .devNonce          = 0,               // restore devNonce
            .joinNonce         = 0,               // restore joinNonce
            .rand              = system_rand,
            .ticks             = system_ticks,    // tell LDL the frequency of the clock source and compensate for uncertainty
            .get_battery_level = 0,
#ifndef LDL_PARAM_TPS
            .tps               = 1000000,
#endif
#ifndef LDL_PARAM_A
            .a                 = 10,
#endif
#ifndef LDL_PARAM_B
            .b                 = 0,
#endif
#ifndef LDL_PARAM_ADVANCE
            .advance           = 0,
#endif
#ifdef LDL_ENABLE_OTAA_DITHER
            .otaaDither        = 100,
#endif
        };
        LDL_MAC_init(&mac, LDL_EU_863_870, &arg);

        // remember to connect the radio events back to the MAC
        LDL_Radio_setEventCallback(&radio, &mac, LDL_MAC_radioEvent);
    }

    /* Optional:
     *
     * Ensure a maximum aggregated duty cycle of ~1%
     *
     * EU_863_870 already includes duty cycle limits. This is to safeguard
     * the example if the region is changed to US_902_928 or AU_915_928.
     *
     * Aggregated Duty Cycle Limit = 1 / (2 ^ setting)
     *
     * */
    LDL_MAC_setMaxDCycle(&mac, 7);

    enable_interrupts();

    for (;;) {

        if (LDL_MAC_ready(&mac)) {

            if (LDL_MAC_joined(&mac)) {
                const char msg[] = "hello world";
                // final argument is NULL since we don't have any specific invocation options
                (void) LDL_MAC_unconfirmedData(&mac, 1, msg, sizeof(msg), NULL);
            } else {
                (void) LDL_MAC_otaa(&mac);
            }
        }

        LDL_MAC_process(&mac);

        // a demonstration of how you might use sleep modes with LDL
        {
            uint32_t ticks_until_next_event = LDL_MAC_ticksUntilNextEvent(&mac);
            if (ticks_until_next_event > 0U) {
                wakeup_after(ticks_until_next_event);
                sleep();
            }
        }
    }
}

void app_handler(void *app, enum ldl_mac_response_type type, const union ldl_mac_response_arg *arg)
{
    switch (type) {

        /* This event is trigger by an earlier call to LDL_MAC_entropy()
         *
         * The value returned is random gathered by the radio driver
         * which can be used to seed stdlib.
         *
         */
        case LDL_MAC_ENTROPY:
            srand(arg->entropy.value);
            break;

        // this is data from confirmed/unconfirmed down frames
        case LDL_MAC_RX:
            (void) arg->rx.port;
            (void) arg->rx.data;
            (void) arg->rx.size;
            break;

        // an opportunity for application to cache session
        case LDL_MAC_SESSION_UPDATED:
            (void) arg->session_updated.session;
            break;

        // an opportunity for application to cache joinNonce
        case LDL_MAC_JOIN_COMPLETE:
            (void) arg->join_complete.joinNonce;
            break;

        // an opportunity for application to cache nextDevNonce
        case LDL_MAC_DEV_NONCE_UPDATED:
            (void) arg->dev_nonce_updated.nextDevNonce;
            break;

        case LDL_MAC_CHANNEL_READY:
        case LDL_MAC_OP_ERROR:
        case LDL_MAC_OP_CANCELLED:
        case LDL_MAC_DATA_COMPLETE:
        case LDL_MAC_DATA_TIMEOUT:
        case LDL_MAC_LINK_STATUS:
        case LDL_MAC_DEVICE_TIME:
        case LDL_MAC_JOIN_EXHAUSTED:
        default:
            break;
    }
}

uint32_t system_ticks(void *app)
{
    // this must read from 32bit ticker
    return 0;
}

long unsigned int system_rand(void *app)
{
    (void) app;
    return rand();
}

void dio0_rising_edge_isr(void)
{
    LDL_Radio_handleInterrupt(&radio, 0);
}

void dio1_rising_edge_isr(void)
{
    LDL_Radio_handleInterrupt(&radio, 1);
}
