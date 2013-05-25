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
*/

/**
 * @file    STM32/IWDG_lld.c
 * @brief   STM32 low level IWDG driver code.
 *
 * @addtogroup IWDG
 * @{
 */

#include "ch.h"
#include "hal.h"

#if HAL_USE_IWDG || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
#define IWDG_FCY 37000
#define IWDG_NTICK 1000

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief IWDG1 IWDG driver identifier.*/
#if STM32_IWDG_USE_IWDG1 || defined(__DOXYGEN__)
IWDGDriver IWDGD1;
#endif

/*===========================================================================*/
/* Driver local variables.                                                   */
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
 * @brief   Low level IWDG driver initialization.
 *
 * @notapi
 */
 
void iwdg_lld_init(void) {

#if STM32_IWDG_USE_IWDG1
  IWDGObjectInit(&IWDGD1);
  IWDGD1.wdg = IWDG;
#endif
}

/**
 * @brief   Configures and activates the IWDG peripheral.
 *
 * @param[in] driver     pointer to the @p IWDGDriver object
 *
 * @notapi
 */
void iwdg_lld_start(IWDGDriver *driver, IWDGConfig *config) {
  driver->config = config;
#if STM32_IWDG_USE_IWDG1
  if (&IWDGD1 == driver) {
    driver->wdg->KR = 0x5555;

    if(config->timeout < 442)
    {
  	  driver->wdg->PR = IWDG_PR_PR & 0;
	  driver->wdg->RLR = config->timeout / IWDG_NTICK * IWDG_FCY / 4;
    }else if (config->timeout < 885)
	{
  	  driver->wdg->PR = IWDG_PR_PR & 1;
	  driver->wdg->RLR = config->timeout / IWDG_NTICK * IWDG_FCY / 8;
	}else if (config->timeout < 1771)
	{
  	  driver->wdg->PR = IWDG_PR_PR & 2;
	  driver->wdg->RLR = config->timeout / IWDG_NTICK * IWDG_FCY / 16;
	}else if (config->timeout < 3542)
	{
  	  driver->wdg->PR = IWDG_PR_PR & 3;
	  driver->wdg->RLR = config->timeout / IWDG_NTICK * IWDG_FCY / 32;
	}else if (config->timeout < 7084)
	{
  	  driver->wdg->PR = IWDG_PR_PR & 4;
	  driver->wdg->RLR = config->timeout / IWDG_NTICK * IWDG_FCY / 64;
	}else if (config->timeout < 14169)
	{
  	  driver->wdg->PR = IWDG_PR_PR & 5;
	  driver->wdg->RLR = config->timeout / IWDG_NTICK * IWDG_FCY / 128;
	}else if (config->timeout < 28339)
	{
  	  driver->wdg->PR = IWDG_PR_PR & 6;
	  driver->wdg->RLR = config->timeout / IWDG_NTICK * IWDG_FCY / 256;
	}
	else return;

//	while(!(driver->wdg->SR && IWDG_SR_PVU ))
//		;
	driver->wdg->KR = 0xAAAA;
    driver->wdg->KR = 0xCCCC;				// start the driver->wdg
    driver->state = IWDG_START;
  }
#endif
}

void iwdg_lld_feed(IWDGDriver * driver) {
  driver->wdg->KR  = 0xAAAA;
}

#endif /* HAL_USE_IWDG */

/** @} */
