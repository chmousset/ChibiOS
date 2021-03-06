/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    LPC17xx/pal_lld.c
 * @brief   LPC17xx GPIO low level driver code.
 *
 * @addtogroup PAL
 * @{
 */

#include "ch.h"
#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/
/**
 * @brief   LPC17xx I/O ports configuration.
 * @details GPIO unit registers initialization.
 *
 * @param[in] config    the LPC17xx ports configuration
 *
 * @notapi
 */
void _pal_lld_init(const PALConfig *config) {

  LPC_GPIO0->FIODIR = config->P0.dir;
  LPC_GPIO1->FIODIR = config->P1.dir;
  LPC_GPIO2->FIODIR = config->P2.dir;
  LPC_GPIO3->FIODIR = config->P3.dir;
  LPC_GPIO4->FIODIR = config->P4.dir;
  LPC_GPIO0->FIOMASK = 0;
  LPC_GPIO1->FIOMASK = 0;
  LPC_GPIO2->FIOMASK = 0;
  LPC_GPIO3->FIOMASK = 0;
  LPC_GPIO4->FIOMASK = 0;
  LPC_GPIO0->FIOPIN = config->P0.data;
  LPC_GPIO1->FIOPIN = config->P1.data;
  LPC_GPIO2->FIOPIN = config->P2.data;
  LPC_GPIO3->FIOPIN = config->P3.data;
  LPC_GPIO4->FIOPIN = config->P4.data;
}

/**
 * @brief   Reads a group of bits.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    group bit offset within the port
 * @return              The group logical states.
 *
 * @notapi
 */
uint32_t _pal_lld_readgroup(ioportid_t port,
                            ioportmask_t mask,
                            uint32_t offset) {

  uint32_t p;

  port->FIOMASK = ~((mask) << offset);
  p = port->FIOPIN;
  port->FIOMASK = 0;
  return p;
}

/**
 * @brief   Writes a group of bits.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    group bit offset within the port
 * @param[in] bits      bits to be written. Values exceeding the group width
 *                      are masked.
 *
 * @notapi
 */
void _pal_lld_writegroup(ioportid_t port,
                         ioportmask_t mask,
                         uint32_t offset,
                         uint32_t bits) {

  port->FIOMASK = ~((mask) << offset);
  port->FIOPIN = bits;
  port->FIOMASK = 0;
}
/**
 * @brief   Pads mode setup.
 * @details This function programs a pads group belonging to the same port
 *          with the specified mode.
 * @note    @p PAL_MODE_UNCONNECTED is implemented as push pull output with
 *          high state.
 * @note    This function does not alter the @p PINSELx registers. Alternate
 *          functions setup must be handled by device-specific code.
 *
 * @param[in] port      the port identifier
 * @param[in] mask      the group mask
 * @param[in] mode      the mode
 *
 * @notapi
 */
void _pal_lld_setgroupmode(ioportid_t port,
                           ioportmask_t mask,
                           iomode_t mode) {

  switch (mode) {
  case PAL_MODE_RESET:
  case PAL_MODE_INPUT:
    port->FIODIR &= ~mask;
    break;
  case PAL_MODE_UNCONNECTED:
    palSetPort(port, PAL_WHOLE_PORT);
  case PAL_MODE_OUTPUT_PUSHPULL:
    port->FIODIR |=  mask;
    break;
  }
}

#endif /* HAL_USE_PAL */

/** @} */
