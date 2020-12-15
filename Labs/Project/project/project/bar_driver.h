/**
 * @mainpage
 * Collection of libraries for AVR-GCC
 * @author Filip Jasek & Vojtech Zboril
 *
 * @file
 * @defgroup bar_driver  <bar_driver.h>
 * @code #include <bar_driver.h> @endcode
 *
 * @brief Function that turn on/of specific amout of leds on bar graf
 *
 * Bar driver simply turns on as much leds as the input value is closer to 0
 * There is need for max value to be defined, so the function knows where to start turning on leds
 *
 *
 *
 *
 * @author Filip Jasek & Vojtech Zboril
 *
 * @version   1.0
 *
 *
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