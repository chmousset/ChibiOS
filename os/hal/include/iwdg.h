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
 * @file    WDG.h
 * @brief   WDG Driver macros and structures.
 *
 * @addtogroup WDG
 * @{
 */

#ifndef _IWDG_H_
#define _IWDG_H_

#if HAL_USE_IWDG || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/
#include "iwdg_lld.h"

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void iwdgInit(void);
  void iwdgStart(IWDGDriver *driver, const IWDGConfig *config);
  void iwdgStop(IWDGDriver *driver);
  void iwdgFeed(IWDGDriver *driver);
  void IWDGObjectInit(IWDGDriver *driver);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_WDG */

#endif /* _WDG_H_ */
