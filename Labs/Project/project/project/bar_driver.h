/*
 * bar_driver.h
 *
 * Created: 02.12.2020 15:49:11
 *  Author: ffili
 */ 


#ifndef BAR_DRIVER_H_

// @brief Control of excition indicator
#define BAR_DRIVER_H_

#define SEGMENT_LATCH	PC0
#define SEGMENT_CLK		PC2
#define SEGMENT_DATA	PB5


// @note initialization for bar segments
void BAR_init(void);

// @note Turning on percent amount of segments compared to max value given by programmer
void BAR_update_shift_regs(uint16_t maxVal, uint16_t currentVal, uint8_t position);


#endif /* BAR_DRIVER_H_ */