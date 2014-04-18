/******************************************************************************
 *
 * Copyright (C) 2011 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC4000/XMC1000 Series                                 **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : App Developer                                                   **
**                                                                            **
** MAY BE CHANGED BY USER [yes/Yes]: Ys                                       **
**                                                                            **
** MODIFICATION DATE : March 22,  2012                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** PM           App Developer                                                 **
*******************************************************************************/

/**
 * @file  CCU4Global.h
 *
 * @brief This file contains all public data structures,enums and function
 *        prototypes.
 */
/* Revision History
 * 22 March    2012   v1.0.0    Initial version
 */
 

#ifndef CCU4GLOBAL_H_
#define CCU4GLOBAL_H_
/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include <DAVE3.h>

/**
  * @ingroup CCU4Global_publicparam
  * @{
  */

/*******************************************************************************
 *                                ENUMERATIONS                                **
 ******************************************************************************/


/*******************************************************************************
 *                                STRUCTURES                                **
 ******************************************************************************/
/**
 * This structure enumerates the CCU4 module number.
 */
typedef struct CCU4Global_HandleType
{
  /**
   * This is the pointer to the CMSIS CCU4 kernel register structure.
   */
   CCU4_GLOBAL_TypeDef* const CC4yKernRegsPtr;
}CCU4Global_HandleType;

/**
 * @}
 */

/**
 * @ingroup CCU4Global_apidoc
 * @{
 */
/*******************************************************************************
 **FUNCTION PROTOTYPES                                                        **
*******************************************************************************/

/**
 * @brief This is the initialization function for the Global App.
 * @return void 
 * <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 * @code
 * #include <DAVE3.h>
 * 
 * int main(void)
 * {
 *  DAVE_Init(); //CCU4GLOBAL_Init is called within DAVE_Init.
 *  
 *  return 0;
 *  
 * }
 * @endcode
 */
void CCU4GLOBAL_Init(void);

#include "CCU4GLOBAL_Conf.h"

/**
 * @}
 */



#endif /*CCUGLOBAL_H_*/
