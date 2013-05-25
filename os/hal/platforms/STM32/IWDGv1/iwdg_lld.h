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
 * @file    STM32/IWDGv1/iwdg_lld.h
 * @brief   STM32 low level IWDG driver header.
 *
 * @addtogroup IWDG
 * @{
 */

#ifndef _IWDG_LLD_H_
#define _IWDG_LLD_H_

#ifndef HAL_USE_IWDG
#define HAL_USE_IWDG 1
#endif

#if HAL_USE_IWDG || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   WDG driver on IWDG enable switch.
 * @details If set to @p TRUE the support for IWDG is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_WDG_USE_IWG) || defined(__DOXYGEN__)
#define STM32_WDG_USE_IWDG               FALSE
#endif


/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if STM32_WDG_USE_IWDG && !STM32_HAS_IWDG
#error "IWDG not present in the selected device"
#endif


/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Structure representing an IWDG driver.
 */
typedef struct IWDGDriver IWDGDriver;

typedef struct {
  /**
   * @brief Timeout (ms) value.
   */
  uint32_t                  timeout;
} IWDGConfig;


/**
 * @brief   enum representing the IWDG state.
 */
typedef enum {IWDG_STOP, IWDG_START} iwdgst_t;

/**
 * @brief   Structure representing an IWDG driver.
 */
struct IWDGDriver {
  /**
   * @brief Current configuration data.
   */
  const IWDGConfig          *config;
  /**
  * @brief Current status of the Watchdog (Stop or Start)
  */
  iwdgst_t                  state;
#if defined(WDG_DRIVER_EXT_FIELDS)
  IWDG_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the IWDG registers block.
   */
  IWDG_TypeDef             *wdg;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_IWDG_USE_IWDG1 && !defined(__DOXYGEN__)
extern IWDGDriver IWDGD1;
#endif


#ifdef __cplusplus
extern "C" {
#endif
  void iwdg_lld_init(void);
  void iwdg_lld_start(IWDGDriver *driver, IWDGConfig *config);
  void iwdg_lld_stop(IWDGDriver *driver);
  void iwdg_lld_feed(IWDGDriver *driver);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_IWDG */

#endif /* _IWDG_LLD_H_ */

/** @} */
