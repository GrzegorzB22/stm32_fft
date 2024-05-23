/*
 * st7735.h
 *
 *  Created on: Feb 19, 2024
 *      Author: Admin
 */

#ifndef INC_ST7735_H_
#define INC_ST7735_H_

#include "main.h"
#include "spi.h"

#define st7735_spi	hspi2
extern SPI_HandleTypeDef st7735_spi;

#define ST7735_WIDTH	160
#define ST7735_HEIGHT	128

#define ST7735_SLPOUT		0x11
#define ST7735_DISPOFF		0x28
#define ST7735_DISPON		0x29
#define ST7735_CASET		0x2a
#define ST7735_RASET		0x2b
#define ST7735_RAMWR		0x2c
#define ST7735_MADCTL		0x36
#define ST7735_COLMOD		0x3a
#define ST7735_FRMCTR1		0xb1
#define ST7735_FRMCTR2		0xb2
#define ST7735_FRMCTR3		0xb3
#define ST7735_INVCTR		0xb4
#define ST7735_PWCTR1		0xc0
#define ST7735_PWCTR2		0xc1
#define ST7735_PWCTR3		0xc2
#define ST7735_PWCTR4		0xc3
#define ST7735_PWCTR5		0xc4
#define ST7735_VMCTR1		0xc5
#define ST7735_GAMCTRP1		0xe0
#define ST7735_GAMCTRN1		0xe1
#define ST7735_EXTCTRL		0xf0


#define BLACK     0x0000
#define RED       0x00F8
#define GREEN     0xE007
#define BLUE      0x1F00
#define YELLOW    0xFFE0
#define MAGENTA   0xF81F
#define CYAN      0x07FF
#define WHITE     0xFFFF

#define ST7735_OFFSET_X		1
#define ST7735_OFFSET_Y		2

#define ST7735_SET_COMMAND	HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_RESET)
#define ST7735_SET_DATA		HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET)

#define SPI_START			HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET)
#define SPI_STOP			HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET)

#define D2C(x)	((x) | 0x100)

void ST7735_Init(void);
void ST7735_Update(void);
void ST7735_WriteChar(uint8_t x, uint8_t y, char c, uint16_t color);
void ST7735_WriteString(uint8_t x, uint8_t y, char *s, uint16_t color);
void ST7735_DrawFFT(float fft_data[], uint16_t FFT_N, uint16_t SAMPLING_N, uint16_t color);
void ST7735_Clear(void);


#endif /* INC_ST7735_H_ */
