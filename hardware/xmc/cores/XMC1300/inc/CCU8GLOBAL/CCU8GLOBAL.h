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
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : September 17, 2012                                     **
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
 * @file  CCU8GLOBAL.h
 *
 * @brief This file contains all public data structures,enums and function
 *        prototypes.
 */
/* Revision History
 * 22 March 2012   v1.0.0    Initial version
 * 17 Sept  2012   v1.0.4    removed the function like macro to abide coding rules 
 */

#ifndef CCU8GLOBAL_H_
#define CCU8GLOBAL_H_
/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#include <DAVE3.h>

/**
  * @ingroup CCU8Global_publicparam
  * @{
  */

/*******************************************************************************
 *                                ENUMERATIONS                                **
 ******************************************************************************/


/*******************************************************************************
 *                                STRUCTURES                                **
 ******************************************************************************/
/**
 * This saves the context of the CCU8Global App.
 */
typedef struct CCU8Global_HandleType
{
  /**
   * This is the pointer to the CMSIS CCU8 kernel register structure.
   */
   CCU8_GLOBAL_TypeDef* const CC8yKernRegsPtr;
}CCU8Global_HandleType;

/**
 * @}
 */

/**
 * @ingroup CCU8Global_apidoc
 * @{
 */
/*******************************************************************************
 **FUNCTION PROTOTYPES                                                        **
*******************************************************************************/

/**
 * @brief This function will initialize the CCU8 module. 
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
 *  DAVE_Init();  //CCU8Global_Init() is called within this function
 *  
 *  return 0;
 *  
 * }
 * @endcode
 */
void CCU8GLOBAL_Init(void);

#include "CCU8GLOBAL_Conf.h"

/**
 * @}
 */



#endif /*CCUGLOBAL_H_*/
