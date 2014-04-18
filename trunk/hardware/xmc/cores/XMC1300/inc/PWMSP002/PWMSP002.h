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
** AUTHOR   : DAVE App Developer                                              **
**                                                                            **
** MAY BE CHANGED BY USER [yes/Yes]: Yes                                      **
**                                                                            **
** MODIFICATION DATE : September 27, 2013                                     **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** KS           DAVE App Developer                                            **
*******************************************************************************/

/**
 * @file  PWMSP002.h
 *
 * @brief This file contains all public data structures,enums and function
 *        prototypes for SinglePhPWM with dead time APP.
 */
/* Revision History
 * 01 Dec 2012   v1.0.16   taken as base version
 * 27 Sep 2013   v1.0.26   added c++ support
 */

#ifndef SINGLEPHPWMDT_H_
#define SINGLEPHPWMDT_H_
/*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "../../inc/LIBS/CCU8PWMLIB.h"
#include <DAVE3.h>

/**
  * @ingroup PWMSP002_publicparam
  * @{
  */
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

#define USE_PWM_LIB

/*******************************************************************************
 *                                ENUMERATIONS                                **
 ******************************************************************************/
/**
 * This structure enumerates the states of the Single Phase PWM with dead time
 * APP.
 */
typedef enum PWMSP002_StateType
{
  /**
   * This is the default state after power on reset
   */
  PWMSP002_UNINITIALIZED,
  /**
   * This is the INITIALIZED state in which APP is initialized as per selected
   * parameters
   */
  PWMSP002_INITIALIZED,
  /**
   * This state indicates that CCU8_CCy slice is running in PWM mode.
   */
  PWMSP002_RUNNING,
  /**
   * This state indicates that CCU8_CCy slice timer is stopped.
   */
  PWMSP002_STOPPED,

} PWMSP002_StateType;

/**
 * This enumerates the error codes of this APP which will be returned from a
 * function as a return parameter.
 */
typedef enum PWMSP002_ErrorCodesType
{
  /**
   * This error code would be returned if the current API operation is not possible
   * because the App is in certain state.
   */
  /**
  * @cond INTERNAL_DOCS
  * @param MODULENAME PWMSP002
  * @endcond
  */
  /**
  * @cond INTERNAL_DOCS
  * @param ERRCODESTRING1 PWMSP002_OPER_NOT_ALLOWED_ERROR
  * @param STRCODESTRING1 The Operation is not allowed in current state.
  * @endcond
  */   
  PWMSP002_OPER_NOT_ALLOWED_ERROR = 1,
  /**
   * This error code means that the parameter passed to an API are invalid
   */
  /**
  * @cond INTERNAL_DOCS
  * @param ERRCODESTRING2 PWMSP002_INVALID_PARAM_ERROR
  * @param STRCODESTRING2 Invalid parameter passed.
  * @endcond
  */   
  PWMSP002_INVALID_PARAM_ERROR,
  /* Debug Log Codes starts here*/
  /**
   * DebugLog Message Id for Function Entry
   */
  /**
  * @cond INTERNAL_DOCS
  * @param ERRCODESTRING3 PWMSP002_FUNCTION_ENTRY
  * @param STRCODESTRING3 Entered Function \%s
  * @endcond
  */      
  PWMSP002_FUNCTION_ENTRY,
  /**
   * DebugLog Message Id for Function Exit
   */
  /**
  * @cond INTERNAL_DOCS
  * @param ERRCODESTRING4 PWMSP002_FUNCTION_EXIT
  * @param STRCODESTRING4 Exited Function \%s
  * @endcond
  */   
  PWMSP002_FUNCTION_EXIT

} PWMSP002_ErrorCodesType;

/**
 * This enumerates the events of the PWMSP002 app.
 */
typedef enum PWMSP002_EventNameType
{
  /**
   * This is the period match interrupt
   */
  PWMSP002_PERIODMATCHEVENT = 0,
  /**
   * This is the compare match while counting UP interrupt
   */
  PWMSP002_COMPAREMATCHEVENT = 2,
  /**
   * This is the external start interrupt i.e. Event 0 interrupt
   */
  PWMSP002_EXTSTARTEVENT = 8,
  /**
   * This is the external stop interrupt i.e. Event 1 interrupt
   */
  PWMSP002_EXTSTOPEVENT = 9,
  /**
   * This is the trap interrupt i.e. Event 2 interrupt
   */
  PWMSP002_TRAPEVENT = 10,
}PWMSP002_EventNameType;

/*******************************************************************************
 *                             STRUCTURES                                     **
 ******************************************************************************/
/**
 * This structure holds the values of the compare register, period register.
 */
typedef struct PWMSP002_TimerRegsType
{
  /**
   * This structure holds the values of the compare register, period register.
   */
  uint32_t CompReg1;
  /**
   * This is the compare register value of channel 2
   */
  uint32_t CompReg2;
  /**
   * This is the period register value
   */
  uint32_t PeriodReg;
  /**
   * This is the current timer register value
   */
  uint32_t TimerReg;
} PWMSP002_TimerRegsType;



/**
 * This structure will hold the configuration parameters which change at run
 * time.
 */
typedef struct PWMSP002_DynamicHandleType
{

/**
 * This is the state of the app.
 */
  PWMSP002_StateType State;
} PWMSP002_DynamicHandleType;

/**
 * This structure holds all the static configuration parameters for the Single
 * Phase PWM with Dead Time APP.
 */
typedef struct PWMSP002_HandleType
{
    /**
     * This parameter tells whether to start the CCU8_CCy slice with external
     * trigger or by SW trigger
     */
    const uint8_t kExtStartTrig;
    /**
     * This parameter tells whether to stop the CCU8_CCy slice with external
     * trigger or by SW trigger
     */
    const uint8_t kExtStopTrig;
    /**
     * This parameter tells whether direct output CCST will be connected to output
     * pin 0 or inverted status output is connected to Out 0.
     */
    const uint8_t kPassiveState0;
    /**
     * This parameter tells whether direct output CCST will be connected to output
     * pin 1 or inverted status output is connected to Out 1.
     */
    const uint8_t kPassiveState1;
    /**
     * This parameter selects the passive level for output 0 - Active High or
     * Active Low
     */
    const uint8_t kPassiveLevel0;
    /**
     * This parameter selects the passive level for output 1 - Active High or
     * Active Low
     */
    const uint8_t kPassiveLevel1;
    /**
     * This parameter is used to store whether CCU8_CCy slice is in single shot
     * mode or in periodic mode
     */
    const uint8_t kTimerMode;
     /**
      * This parameter tells whether timer concatenation is required or not.
      */
    const uint8_t kTimerConcatenation;
    /**
      * This indicates whether TRAP signal will have an effect on output signal.
      */
    const uint8_t kTrapEnable;
    /**
      * This configures the synchronization with the PWM signal is required or
      * not.
      */
    const uint8_t kTrapSync;
    /**
     * This parameter gives the active level of the Trap signal
     */
    const uint8_t kTrapLevel;  
    /**
     * This indicates whether to exit from TRAP state automatically when TRAP
     * condition is removed or SW trigger is required to exit from the TRAP state.
     */
    const uint8_t kTrapExitControl;
    /**
     * This parameter saves the dither compare value
     */
    const uint8_t kDitherCompare; 
    /**
     * This is the dead time prescalar divider value.
     */
    const uint8_t kDeadTimePrescalar;
    /**
     * This parameter configures dither mode.
     */
    const uint8_t kDitherSetting;
    /**
     * This tells whether to enable shadow transfer in this App
     * or it will be taken care by some other app
     */
    const uint8_t ShadowTransfer;
    /**
     * This tells whether to clear IDLE mode in this App
     * or it will be taken care by some other app
     */
    const uint8_t Start;    
    /**
     * This decides whether to start the app after initialization
     */  
    const uint8_t StartControl;       
    /**
    * This is the  the falling dead time value for channel 1
    */
   const uint16_t kFallingDeadTime;
   /**
    * This is the the rising dead time value for channel 1
    */
   const uint16_t kRisingDeadTime;    
    
    /**
   * This is the resolution of the CCU8
   */
  const float kResolution;
  /**
   * This is the compare register value of channel 1 which corresponds to
   * initial duty cycle
   */
  const uint32_t kCompareValue1;
  /**
   * This is the compare register value of channel 2 which corresponds to
   * initial duty cycle. This will be used in case of asymmetric PWM mode.
   */
  const uint32_t kCompareValue2;
  /**
   * This is the prescalar divider value.
   */
  const uint32_t kCCUPrescalar;
  /**
   * This parameter gives the active edge of the external start signal
   */
  const CCU8PWMLIB_EdgeTriggerType kStartEdge;
  /**
   * This parameter gives the active edge of the external stop signal
   */
  const CCU8PWMLIB_EdgeTriggerType kStopEdge;
  /**
    * Period value computed as per counting mode
    */
  const uint32_t kPeriodVal;
 /**
   * This is pointer to the CMSIS CCU8 kernel register structure.
   */
  CCU8_GLOBAL_TypeDef* const CC8yKernRegsPtr;
  /**
   * This is pointer to the CMSIS CCU8 slice register structure.
   */
  CCU8_CC8_TypeDef* const CC8yRegsPtr;
  /**
   * This is pointer to the CMSIS CCU8 slice register structure.
   */
  CCU8_CC8_TypeDef* const CC8yRegs1Ptr;
/**
 * This is the ointer to the dynamic handle
 */
  PWMSP002_DynamicHandleType* const DynamicHandleType;
  /**
   * This is the counting mode of the timer
   */
  const CCU8PWMLIB_CountingModeType CountingMode;
  /**
   * This is the functionality of the external stop
   */
  const CCU8PWMLIB_ExtStopConfigType ExtStopConfig;
  /**
   * This is the dead time configuration
   */
  const CCU8PWMLIB_DeadTimeConfType DeadTimeConf;
  /** This is the compare mode of the timer - symmetric/asymmetric
   */
  const CCU8PWMLIB_CompareModeType CompareMode;
  /**
   * This is the functionality of the external stop
   */
  const CCU8PWMLIB_ExtStartConfigType ExtStartConfig;
  /**
   * This saves the slice number of the first slice.
   */
  const CCU8PWMLIB_CCUInUseType FirstSlice;
  /**
   * This saves the slice number od the second slice in case of timer concatenation
   */
  const CCU8PWMLIB_CCUInUseType SecondSlice;
  /**
   * Bitmask for shadow transfer as per slice number
   */
  const uint32_t ShadowTransferMask;
  /**
   * Bitmask for clearing IDLE mask as per slice used
    */
  const uint32_t StartMask;
  /**
   * This decides whether to enable interrupts at initialization time. This stores the information in a format of 32-bit register (INTE)
   * with a bit-field for each interrupt.
   */
  const uint32_t InterruptControl;
 /**
   * This is the function pointer for the SetCompare function
   */
  CCU8PWMLIB_SetCompareFuncionPtr SetCompareFuncPtr;
  /**
   * This is the function pointer for the SetDutyCycle function
   */
  CCU8PWMLIB_SetDutyFunctionPtr SetDutyFuncPtr;
} PWMSP002_HandleType;

/**
 * @}
 */

/**
 * @ingroup PWMSP002_apidoc
 * @{
 */
/*******************************************************************************
 **FUNCTION PROTOTYPES                                                        **
*******************************************************************************/
/**
 * @brief This function is used to initialize the APP.
 * It will configure CCU8_CCy slice registers with the selected PWM parameters.
 * 
 * @return void\n
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
 *  DAVE_Init(); //PWMSP002_Init is called within DAVE_Init.
 *  
 *  return 0;
 *  
 * }
 * @endcode
 */
void PWMSP002_Init(void);

/**
 * @brief This will reset the CCU8_CCy slice registers to default state.
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * else
 * PWMSP002_OPER_NOT_ALLOWED_ERROR <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 * @code
 * #include <DAVE3.h>
 * 
 * int main(void)
 * {
 * status_t Status;
 *  DAVE_Init(); //PWMSP002_Init is called within DAVE_Init.
 *  //....
 *  Status = PWMSP002_Deinit((PWMSP002_HandleType*)&PWMSP002_Handle0);
 *  return 0;
 *  
 * }
 * @endcode
 */
status_t PWMSP002_Deinit(const PWMSP002_HandleType* HandlePtr);

/**
 * @brief This will start the Single Phase PWM with Dead Time APP which will in
 * turn start the CCU8_CCy slice.\n
 * <b>This function needs to be called to start the App
 * even if External Start feature of CCU8 is configured. </b>
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called in the state other
 * than PWMSP002_INITIALIZED <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 *
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
 *  status_t Status;
 *  DAVE_Init();
 *  //This needs to be called if "Start after initialization" is unchecked
 *  Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
 *  if (Status == (uint32_t)DAVEApp_SUCCESS)
 *  {
 *    //Do something
 *  }
 *  return 0;
 * }
 * @endcode
*/
status_t PWMSP002_Start(const PWMSP002_HandleType* HandlePtr);

/**
 * @brief This will stop the Single Phase PWM with Dead Time APP which
 * will in turn stop the CCU8_CCy slice.\n
 * <b> This function needs to be called even if external stop feature is configured </b>
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when not in the
 * state PWMSP002_RUNNING or   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 *
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
 *  status_t Status;
 *  DAVE_Init();
 *  *  //This needs to be called if "Start after initialization" is unchecked
 *  
 *  Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
 *  if (Status == (uint32_t)DAVEApp_SUCCESS)
 *  {
 *    //Do something
 *  }
 *  Status = PWMSP002_Stop((PWMSP002_HandleType*)&PWMSP002_Handle0);
 *  return 0;
 * }
 * @endcode
*/
status_t PWMSP002_Stop(const PWMSP002_HandleType* HandlePtr);

/**
 * @brief This function will modify the duty cycle of the output waveform
 * which will change the pulse width.\n
 * <b>Duty cycle is given in terms of the compare register value and not in terms
 * of the percentage.</b>
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @param[in]   Compare1 It corresponds to compare register 1 value.
 * @param[in]   Compare2 It corresponds to compare register 2 value. \n
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 *
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
    status_t Status;
    uint32_t Counter;
    DAVE_Init();
    *  //This needs to be called if "Start after initialization" is unchecked
    Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);
    // Change compare register value
    // CR1 = 2500
    // CR2 = 5000
    //if Period register is 10000 the this will give 25% duty cycle in edge-aligned mode
    Status = PWMSP002_SetCompare((PWMSP002_HandleType*)&PWMSP002_Handle0,2500,5000);
    for(Counter = 0;Counter <=0xFFFF;Counter++);

    while(1);
    return 0;
}
* @endcode
*/
status_t PWMSP002_SetCompare
(
  const PWMSP002_HandleType* HandlePtr,
  uint32_t Compare1,
  uint32_t Compare2
  
);

/**
 * @brief This function will modify the duty cycle of the output waveform
 * which will change the pulse width.\n
 * <b>Duty cycle is given in terms of percentage.</b>
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @param[in]   DutyCycle It corresponds to duty cycle in percentage.
 * @param[in]   Shift It controls the duty cycle value.
 * @param[in]   Sign It controls addition and subtraction of shift
 * Sign = 0: Compare value is incremented by shift. This is not allowed in edge-aligned.
 * Sign = 1: Compare value is decremented by shift.
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 *
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
    status_t Status;
    uint32_t Counter;
*  //This needs to be called if "Start after initialization" is unchecked
    Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);
    // Change duty cycle value
    //It should give 60 % duty cycle. Compare register1 value is decreased by 100
    // and compare register1 value is increased by 100 to get asymmetric waveform with
    //60% duty cycle
    Status = PWMSP002_SetDutyCycle((PWMSP002_HandleType*)&PWMSP002_Handle0,60,100,0);
    for(Counter = 0;Counter <=0xFFFF;Counter++);

    while(1);
    return 0;
}
* @endcode
*/
status_t PWMSP002_SetDutyCycle
(
  const PWMSP002_HandleType* HandlePtr,
  float DutyCycle,
  uint32_t Shift,
  uint8_t Sign
);

/**
 * @brief This function will modify the pwm frequency of the output waveform
 * which will change the pulse width.\n
 * <b>In case of timer concatenation,given value is split into two 16-bit values
 * and they are programmed in Second and First slice.\n
 * e.g. 0x80000010 value is written as 0x8000 as Period register of Second slice
 * and 0x0010 as period register of first slice.
 * Total PWM period is ((0x8000 +1) * 0x0010) + 1.
 * </b>
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @param[in]   PwmFreq It corresponds to period register's value.
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 *
 * @code
 * #include <DAVE3.h>
 * #include "../../inc/PWMSP002/PWMSP002Conf.h"
 *
 * int main(void)
 * {
    status_t Status;
    uint32_t Counter;
    DAVE_Init();
*  //This needs to be called if "Start after initialization" is unchecked
    Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);
    // Change PWM frequency
    //  PR = 50000
    Status = PWMSP002_SetPeriod((PWMSP002_HandleType*)&PWMSP002_Handle0, 50000);
    //After changing period, set the duty cycle explicitly.
    Status = PWMSP002_SetDutyCycle((PWMSP002_HandleType*)&PWMSP002_Handle0,60,0,0);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);
    while(1);
    return 0;
}
* @endcode
 */
status_t PWMSP002_SetPeriod
(
  const PWMSP002_HandleType* HandlePtr,
  uint32_t PwmFreq
);


/**
 * @brief This function will modify the pwm frequency and duty cycle of the output waveform\n
 * PWM frequency is given in terms of the period register value and duty cycle is given in terms
 * of the compare register value.
 * <b>In case of timer concatenation,period register value is split into two 16-bit values
 * and they are programmed in Second and First slice.\n
 * e.g. 0x80000010 value is written as 0x8000 as Period register of Second slice
 * and 0x0010 as period register of first slice.
 * Total PWM period is ((0x8000 +1) * 0x0010) + 1.
 * </b>
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @param[in]   PwmFreq It corresponds to period register's value.
 * @param[in]   Compare1 It corresponds to compare register 1 value.
 * @param[in]   Compare2 It corresponds to compare register 2 value. \n
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 *
 * @code
 * #include <DAVE3.h>
 * #include "../../inc/PWMSP002/PWMSP002Conf.h"
 *
 * int main(void)
 * {
    status_t Status;
    uint32_t Counter;
    DAVE_Init();
*  //This needs to be called if "Start after initialization" is unchecked
    Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);
    // Change PWM frequency
    //  PR = 50000
    Status = PWMSP002_SetPeriodAndCompare((PWMSP002_HandleType*)&PWMSP002_Handle0, 50000, 1000, 2000);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);
    while(1);
    return 0;
}
* @endcode
 */
status_t PWMSP002_SetPeriodAndCompare
(
  const PWMSP002_HandleType* HandlePtr,
  uint32_t PwmFreq,
  uint32_t Compare1,
  uint32_t Compare2
);

/**
 * @brief This function will modify the pwm frequency of the output waveform. \n
 * PWM frequency is given in hertz.
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @param[in]   PwmFreq It corresponds to frequency in hertz
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 *
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
    status_t Status;
    uint32_t Counter;
    DAVE_Init();
    //This should be called if "Start after initialization" is unchecked
    Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);
    // Change duty cycle value
    //It should give 60 % duty cycle
    Status = PWMSP002_SetDutyCycle((PWMSP002_HandleType*)&PWMSP002_Handle0,60,0,0);
    // Change PWM frequency to 2500 Hz
    Status = PWMSP002_SetPwmFreq((PWMSP002_HandleType*)&PWMSP002_Handle0, 2500);
    //After changing frequency, set the duty cycle explicitly.
    Status = PWMSP002_SetDutyCycle((PWMSP002_HandleType*)&PWMSP002_Handle0,60,0,0);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);

    while(1);
    return 0;
}
* @endcode
 */
status_t PWMSP002_SetPwmFreq
(
  const PWMSP002_HandleType* HandlePtr,
  float PwmFreq
);

/**
 * @brief This function will modify the pwm frequency and duty cycle of the output waveform. \n
 * PWM frequency is given in Hertz and duty cycle in %. \n
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @param[in]   PwmFreq It corresponds to frequency in hertz
 * @param[in]   DutyCycle It corresponds to duty cycle in percentage.
 * @param[in]   Shift It controls the duty cycle value.
 * @param[in]   Sign It controls addition and subtraction of shift \n
 * Sign = 0: Compare value is incremented by shift. This is not allowed in edge-aligned.
 * Sign = 1: Compare value is decremented by shift.
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 *
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
    status_t Status;
    uint32_t Counter;
    DAVE_Init();
    //This should be called if "Start after initialization" is unchecked
    Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
    // Wait to observe the waveform
    for(Counter = 0;Counter <=0xFFFF;Counter++);
    // Change PWM frequency to 2500 Hz
    Status = PWMSP002_SetPwmFreqAndDutyCycle((PWMSP002_HandleType*)&PWMSP002_Handle0, 2500, 10, 0,0);

    while(1);
    return 0;
}
* @endcode
 */
status_t PWMSP002_SetPwmFreqAndDutyCycle
(
  const PWMSP002_HandleType* HandlePtr,
  float PwmFreq,
  float DutyCycle,
  uint32_t Shift,
  uint8_t Sign    
);

/**
 * @brief This will update the timer register value when timer is stopped.
 * This is used to set the starting value of the timer. It is useful API in the
 * single shot mode.
 *
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @param[in]   TimerVal
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_RUNNING   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 *  * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      DAVE_Init();
      //This will load the timer with 500. 
      PWMSP002_SetTimerVal((PWMSP002_HandleType*)&PWMSP002_Handle0, 500);
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      while(1);
      return 0; 
   }
   * @endcode
 */
status_t PWMSP002_SetTimerVal
(
  const PWMSP002_HandleType* HandlePtr,
  uint32_t TimerVal
);

/**
 * @brief This will request the update of the period register, compare register
 * values from the respective shadow transfers.
 * This function needs to be called when shadow compare and period registers are
 * updated explicitely by top level app.\n
 * <b>NOTE: </b> SetDutyCycle and SetPwmFreq functions handle shadow
 * transfer request. No need to call this function after changing the duty cycle
 * and PWM frequency.
 *  @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED   <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;

      DAVE_Init();
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      //This is the utility function to initiate the shadow transfer. 
      //This needs to be called if period or compare value is explicitly changed by the user
      Status = PWMSP002_SWRequestShadowTransfer((PWMSP002_HandleType*)&PWMSP002_Handle0);

      while(1);
      return 0; 
   }
* @endcode
 */
status_t PWMSP002_SWRequestShadowTransfer
(
  const PWMSP002_HandleType* HandlePtr
);

/**
 * @brief This function will read the period register value.This will be useful
 * to calculate the compare register values.
 * @param[out]  PeriodRegPtr
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED   state <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 * * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      uint32_t Period;
      DAVE_Init();
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      //Period will get the period register value. 
      Status = PWMSP002_GetPeriodReg((PWMSP002_HandleType*)&PWMSP002_Handle0, &Period);

      while(1);
      return 0; 
   }
* @endcode
 */
status_t PWMSP002_GetPeriodReg
(
  const PWMSP002_HandleType* HandlePtr,
  uint32_t* PeriodRegPtr
);

/**
 * @brief This function will reset the trap flag by checking whether trap
 * condition is reset.
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_INITIALIZED or PWMSP002_RUNNING state <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      DAVE_Init();
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      //Reset the trap flag if SW exit is selected
      Status = PWMSP002_ResetTrapFlag((PWMSP002_HandleType*)&PWMSP002_Handle0);

      while(1);
      return 0; 
   }
* @endcode
 */
status_t PWMSP002_ResetTrapFlag(const PWMSP002_HandleType* HandlePtr);

/**
 * @brief This function will read the timer values of compare register and
 * period register.
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @param[in]   TimerRegsPtr Pointer to PWMSP002_TimerRegsType structure
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED  \n
 * PWMSP002_INVALID_PARAM_ERROR: If TimerRegs* is invalid. <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      PWMSP002_TimerRegsType TimerVal;
      DAVE_Init();
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      Status = PWMSP002_GetTimerRegsVal((PWMSP002_HandleType*)&PWMSP002_Handle0, &TimerVal);

      while(1);
      return 0; 
   }
* @endcode
 */
status_t PWMSP002_GetTimerRegsVal
(
  const PWMSP002_HandleType* HandlePtr,
  PWMSP002_TimerRegsType* TimerRegsPtr
);

/**
 * @brief This function will read the timer status whether timer is running or
 * idle.
 * @param[out] TimerStatusPtr
 * @param[in]   HandlePtr Pointer to PWMSP002_HandleType structure
 * @return status_t\n
 * DAVEApp_SUCCESS: if function is successful\n
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If this function is called when in the state
 * PWMSP002_UNINITIALIZED  . <BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      uint32_t TimerStatus;
      DAVE_Init();
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      Status = PWMSP002_GetTimerStatus((PWMSP002_HandleType*)&PWMSP002_Handle0, &TimerStatus);
      if(TimerStatus == (uint8_t)SET)
      {
        //Timer is running
      }
      while(1);
      return 0; 
   }
   * @endcode
 */
status_t PWMSP002_GetTimerStatus
(
 const PWMSP002_HandleType* HandlePtr,
 uint32_t* TimerStatusPtr
);

/**
 * @brief This function will enable the event. This should be called by the user first
 * for interrupt handling.
 *
 * @param [in] HandlePtr pointer to the Instance variable<BR>
 * @param [in] Event Event to be enabled <BR>
 * @return status_t<BR>
 * DAVEApp_SUCCESS: if the function is successful<BR>
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If the function is called in
 * PWMSP002_UNINITIALIZED State.<BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 *  * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      DAVE_Init();
      //This needs to be called when "Enable interrupt at initialization" is not checked.
      Status = PWMSP002_EnableEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      while(1);
      return 0; 
   }
* @endcode 
 */
status_t PWMSP002_EnableEvent
(
     const PWMSP002_HandleType * HandlePtr,
     const PWMSP002_EventNameType Event
);

/**
 * @brief This function will disable the event.
 *
 * @param [in] HandlePtr pointer to the Instance variable<BR>
 * @param [in] Event Event to be disabled <BR>
 * @return status_t<BR>
 * DAVEApp_SUCCESS: if the function is successful<BR>
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If the function is called in
 * PWMSP002_UNINITIALIZED State.<BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 *  * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      DAVE_Init();
      //This needs to be called when "Enable interrupt at initialization" is not checked.
      Status = PWMSP002_EnableEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      //Disable the period match interrupt
      Status = PWMSP002_DisableEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
      while(1);
      return 0; 
   }
* @endcode 
 */
status_t PWMSP002_DisableEvent
(
    const PWMSP002_HandleType * HandlePtr,
    const PWMSP002_EventNameType Event
);

/**
 * @brief This function will clear the pending event.
 *
 * @param [in] HandlePtr pointer to the Instance variable<BR>
 * @param [in] Event Event to be cleared <BR>
 * @return status_t<BR>
 * DAVEApp_SUCCESS: if the function is successful<BR>
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If the function is called in
 * PWMSP002_UNINITIALIZED State.<BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 *  * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      DAVE_Init();
      //This needs to be called when "Enable interrupt at initialization" is not checked.
      Status = PWMSP002_EnableEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      while(1);
      return 0; 
   }
   
   void PWMSP002_PeriodMatchInterruptHandler(void)
   {
     //do something and then reset the event
     PWMSP002_ClearPendingEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
   }
* @endcode 
 */
status_t PWMSP002_ClearPendingEvent
(
    const PWMSP002_HandleType * HandlePtr,
    const PWMSP002_EventNameType Event
);

/**
 * @brief This function will forcefully set the event.This function should not be called within
 * interrut handler to avoid infinite loop.
 *
 * @param [in] HandlePtr pointer to the Instance variable<BR>
 * @param [in] Event Event to be set <BR>
 * @return status_t<BR>
 * DAVEApp_SUCCESS: if the function is successful<BR>
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If the function is called in
 * PWMSP002_UNINITIALIZED State.<BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 * * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      DAVE_Init();
      //This needs to be called when "Enable interrupt at initialization" is not checked.
      Status = PWMSP002_EnableEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      //forcefuly set the event
      Status = PWMSP002_SetPendingEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
      while(1);
      return 0; 
   }
* @endcode 
 */
status_t PWMSP002_SetPendingEvent
(
    const PWMSP002_HandleType * HandlePtr,
    const PWMSP002_EventNameType Event
);

/**
 * @brief This function will check whether given event is set.
 *
 * @param [in] HandlePtr pointer to the Instance variable<BR>
 * @param [in] Event Event to be set <BR>
 * @param [in] EvtStatus Status of the eventwhether it is set <BR>
 * @return status_t<BR>
 * DAVEApp_SUCCESS: if the function is successful<BR>
 * PWMSP002_OPER_NOT_ALLOWED_ERROR: If the function is called in
 * PWMSP002_UNINITIALIZED State.<BR>
 *
 * <b>Reentrancy:  Yes</b><BR>
 * <b>Sync/Async:  Synchronous</b><BR>
 * 
 * * @code
 * #include <DAVE3.h>
 *
 * int main(void)
 * {
      status_t Status;
      DAVE_Init();
      //This needs to be called when "Enable interrupt at initialization" is not checked.
      Status = PWMSP002_EnableEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
       //Start needs to be called only when "Start after initialization" is not checked
      Status = PWMSP002_Start((PWMSP002_HandleType*)&PWMSP002_Handle0);
      while(1);
      return 0; 
   }
   
   void PWMSP002_PeriodMatchInterruptHandler(void)
   {
     uint8_t EvtStatus;
     PWMSP002_GetPendingEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT, &EvtStatus);
     if(EvtStatus == (uint8_t)SET)
     {
       //do something and then reset the event
       PWMSP002_ClearPendingEvent((PWMSP002_HandleType*)&PWMSP002_Handle0, PWMSP002_PERIODMATCHEVENT);
     }
* @endcode
 */
status_t PWMSP002_GetPendingEvent
(
    const PWMSP002_HandleType * HandlePtr,
    const PWMSP002_EventNameType Event,
    uint8_t* EvtStatus
);

#include "PWMSP002_Conf.h"

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* SINGLEPHPWMDT_H_ */

