/*
    Copyright (C) Charles-Henri Mousset

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
 * @file    iwdg.c
 * @brief   Independant Watchdog Timer Driver code.
 *
 * @addtogroup WDG
 * @{
 */

#include "ch.h"
#include "hal.h"
#if HAL_USE_IWDG || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   IWDG Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void iwdgInit(void) {

  iwdg_lld_init();
}


/**
 * @brief   'Feed the dog' - Reload the IWDG counter to avoid reset.
 *
 * @param[in] driver     pointer to the @p IWDRDriver object
 *
 * @api
 */
void iwdgFeed(IWDGDriver *driver) {
	iwdg_lld_feed(driver);
}

/**
 * @brief   Configures and activates the IWDG peripheral.
 *
 * @param[in] driver     pointer to the @p IWDGDriver object
 * @param[in] config    pointer to the @p IWDGConfig object
 *
 * @api
 */
void iwdgStart(IWDGDriver *driver, const IWDGConfig *config) {
  driver->config = config;
  iwdg_lld_start(driver);
}

/**
 * @brief   Initializes the standard part of a @p IWDGDriver structure.
 *
 * @param[out] driver    pointer to the @p IWDGDriver object
 *
 * @init
 */
void IWDGObjectInit(IWDGDriver *driver){
  driver->config = NULL;
  driver->state = IWDG_STOP;
}

#endif
