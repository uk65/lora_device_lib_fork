
#include "stm32l1xx.h"
#include "spi-board.h"

void spiInit(void)
{
#if 0
    // PA4: SPI1_NSS, PA5: SPI1_SCK, PA6: SPI1_MISO, PA7: SPI1_MOSI
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL |= GPIO_CRL_MODE5 | GPIO_CRL_CNF5;   // output high-speed alternate open-drain
    GPIOA->CRL |= GPIO_CRL_MODE7 | GPIO_CRL_CNF7;   // output high-speed alternate open-drain

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    SPI1->CR1 |= SPI_CR1_SPE;
#endif
}

uint8_t spiTransfer(uint8_t byte)
{
    SPI1->DR = byte;
    while (! (SPI1->CR2 & SPI_CR2_TXEIE));

    return SPI1->DR;
}



