/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for STMicroelectronics STM32L-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_UUNIMITTARI
#define BOARD_NAME              "Uunimittari"

/*
 * Board frequencies.
 * NOTE: The HSE crystal is not fitted by default on the board.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            8000000

/*
 * MCU type as defined in the ST header file stm32l1xx.h.
 */
#define STM32L1XX_MD

/*
 * IO pins assignments.
 */
#define GPIOA_BUTTONS		0
#define GPIOA_VBUS		1
#define GPIOA_VPOS_CTRL		2
#define GPIOA_VNEG_CTRL		3
#define GPIOA_VBORDER_CTRL	4
#define GPIOA_SPEAKER_OUT	5
#define GPIOA_NTC_IN 6
#define GPIOA_NTC_POWER 7
#define GPIOA_RF_POWER		9
#define GPIOA_USART1_RX		10
#define GPIOA_USBDM		11
#define GPIOA_USBDP		12
#define GPIOA_SWDIO		13
#define GPIOA_SWCLK		14
#define GPIOA_EINK_VDD		15

#define GPIOB_EINK_PWR		0
#define GPIOB_EINK_SPV		1
#define GPIOB_EINK_CKV		2
#define GPIOB_EINK_CL		3
#define GPIOB_EINK_LE		4
#define GPIOB_EINK_OE		5
#define GPIOB_EINK_SHR		6
#define GPIOB_EINK_SPH		7
#define GPIOB_EINK_D0		8
#define GPIOB_EINK_D1		9
#define GPIOB_EINK_D2		10
#define GPIOB_EINK_D3		11
#define GPIOB_EINK_D4		12
#define GPIOB_EINK_D5		13
#define GPIOB_EINK_D6		14
#define GPIOB_EINK_D7		15

#define GPIOC_EINK_GMODE	13
#define GPIOC_OSC32_IN		14
#define GPIOC_OSC32_OUT		15

#define GPIOH_LED		1

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_400K(n)          (0U << ((n) * 2))
#define PIN_OSPEED_2M(n)            (1U << ((n) * 2))
#define PIN_OSPEED_10M(n)           (2U << ((n) * 2))
#define PIN_OSPEED_40M(n)           (3U << ((n) * 2))
#define PIN_PUDR_FLOATING(n)        (0U << ((n) * 2))
#define PIN_PUDR_PULLUP(n)          (1U << ((n) * 2))
#define PIN_PUDR_PULLDOWN(n)        (2U << ((n) * 2))
#define PIN_AFIO_AF(n, v)           ((v##U) << ((n % 8) * 4))

/*
 * Port A setup.
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_BUTTONS) |       \
                                     PIN_MODE_INPUT(GPIOA_VBUS) |           \
                                     PIN_MODE_OUTPUT(GPIOA_VPOS_CTRL) |     \
                                     PIN_MODE_OUTPUT(GPIOA_VNEG_CTRL) |     \
                                     PIN_MODE_INPUT(GPIOA_VBORDER_CTRL) |  \
                                     PIN_MODE_ANALOG(GPIOA_SPEAKER_OUT) |   \
                                     PIN_MODE_ANALOG(GPIOA_NTC_IN) |        \
                                     PIN_MODE_OUTPUT(GPIOA_NTC_POWER) |     \
                                     PIN_MODE_INPUT(8) |                    \
                                     PIN_MODE_OUTPUT(GPIOA_RF_POWER) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_USART1_RX) |  \
                                     PIN_MODE_INPUT(GPIOA_USBDM) |          \
                                     PIN_MODE_INPUT(GPIOA_USBDP) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_EINK_VDD))
#define VAL_GPIOA_OTYPER            0x00000000
#define VAL_GPIOA_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOA_PUPDR             (PIN_PUDR_PULLDOWN(GPIOA_VBUS) |        \
                                     PIN_PUDR_FLOATING(GPIOA_NTC_IN) |      \
                                     PIN_PUDR_PULLUP(8) |                   \
                                     PIN_PUDR_PULLDOWN(GPIOA_VBORDER_CTRL) | \
                                     PIN_PUDR_PULLDOWN(GPIOA_USART1_RX) | \
                                     PIN_PUDR_PULLDOWN(GPIOA_EINK_VDD))
#define VAL_GPIOA_ODR               0x00000000
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_BUTTONS, 0))
                                     
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_USART1_RX, 7) | \
                                     PIN_AFIO_AF(GPIOA_USBDM, 10) | \
                                     PIN_AFIO_AF(GPIOA_USBDP, 10) | \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0) | \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0))

/*
 * Port B setup.
 */
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_EINK_PWR) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_SPV) |      \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_CKV) |      \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_CL) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_LE) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_OE) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_SHR) |      \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_SPH) |      \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_D0) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_D1) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_D2) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_D3) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_D4) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_D5) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_D6) |       \
                                     PIN_MODE_OUTPUT(GPIOB_EINK_D7))
                                     
#define VAL_GPIOB_OTYPER            0x00000000
#define VAL_GPIOB_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOB_PUPDR             0x00000000
#define VAL_GPIOB_ODR               0x00000000
#define VAL_GPIOB_AFRL              0x00000000
#define VAL_GPIOB_AFRH              0x00000000

/*
 * Port C setup.
 */
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_EINK_GMODE) |    \
                                     PIN_MODE_ANALOG(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_ANALOG(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            0x00000000
#define VAL_GPIOC_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOC_PUPDR             0x00000000
#define VAL_GPIOC_ODR               0x00000000
#define VAL_GPIOC_AFRL              0x00000000
#define VAL_GPIOC_AFRH              0x00000000

/*
 * Port H setup.
 */
#define VAL_GPIOH_MODER             (PIN_MODE_OUTPUT(GPIOH_LED) | \
                                     PIN_MODE_ANALOG(0))
#define VAL_GPIOH_OTYPER            0x00000000
#define VAL_GPIOH_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOH_PUPDR             0x00000000
#define VAL_GPIOH_ODR               0x00000000
#define VAL_GPIOH_AFRL              0x00000000
#define VAL_GPIOH_AFRH              0x00000000

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
