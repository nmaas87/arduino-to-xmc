/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2012)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC1000 Series   			                          **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : App Developer                                                   **
**                                                                            **
** MAY BE CHANGED BY USER [yes/no]: Yes                                       **
**                                                                            **
** MODIFICATION DATE : Feb 04, 2013                                           **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** PAE        App Developer                                                   **
*******************************************************************************/
/**
 * @file   NVIC_SR101.h
 *
 * @brief  This file has the definitions of enums,functions
 *
 */
/* Revision History */
/* 19-12-12 v0.1.0 Inital version
 * 04-02-13 v0.1.3 version updated
 */
#ifndef NVIC_SR101_H_
#define NVIC_SR101_H_

/******************************************************************************
**                      Include Files                                        **
******************************************************************************/

#include <DAVE3.h>

/******************************************************************************
**                      Global Macro Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Global Type Definitions                              **
******************************************************************************/

/**
 * @brief   Callback function prototype
 */
typedef void (*NVIC_SR101_CallbackType)(uint32_t CbArg);


/**
 * @ingroup NVIC_SR101_publicparam
 * @{
 */
/**
 * @brief This data structure is used for selecting the
 * SCU.SR1 Event for the  specified driver API functions.
 *
 */
typedef enum NVIC_SR101_InterruptType{
	/**
	 * Standby Clock Event
	 */
	NVIC_SR101_SBYCLKFI,
	/**
	 * VDDP Event
	 */
	NVIC_SR101_VDDPI,
	/**
	 * VDROP Event
	 */
	NVIC_SR101_VDROPI,
	/**
	 * VCLIP Event
	 */
	NVIC_SR101_VCLIPI,
	/**
	 * TSE DONE Event
	 */
	NVIC_SR101_TSE_DONE,
	/**
	 * TSE HIGH Event
	 */
	NVIC_SR101_TSE_HIGH,
	/**
	 * TSE LOW Event
	 */
	NVIC_SR101_TSE_LOW,
	/**
	 * Pre Warning Event
	 */
	NVIC_SR101_PRWARN,
	/**
	 * Periodic Event
	 */
	NVIC_SR101_PI,
	/**
	 * Alarm Event
	 */
	NVIC_SR101_AI,
	/**
	 * RTC Control Event
	 */
	NVIC_SR101_RTC_CTR,
	/**
	 * RTC ATIM0 Event
	 */
	NVIC_SR101_RTC_ATIM0,
	/**
	 * RTC ATIM1 Event
	 */
	NVIC_SR101_RTC_ATIM1,
	/**
	 * RTC TIM0 Event
	 */
	NVIC_SR101_RTC_TIM0,
	/**
	 * RTC TIM1 Event
	 */
	NVIC_SR101_RTC_TIM1,
	/**
	 * this is not an event (count of the max event possible)
	 */
	NVIC_SR101_MAX
 }NVIC_SR101_InterruptType;


 /**
  * @ingroup NVIC_SR101_publicparam
  * @{
  */
 /**
  * @brief This Enumeration is used for getting status of Register CallBack for
  * SCU.SR1 Event for the  specified driver API functions.
  *
  */
 typedef enum NVIC_SR101_RegisterCbStatusType{
	/**
	 * Callback Success
	 */
 	NVIC_SR101_REGISTER_SUCCESS,
	/**
	 * Callback Failure
	 */
 	NVIC_SR101_REGISTER_FAIL
  }NVIC_SR101_RegisterCbStatusType;


  /**
   * @ingroup NVIC_SR101_publicparam
   * @{
   */
 /**
  * @brief Structure which holds NVIC_SR101 Error Codes
  */
 typedef enum NVIC_SR101_ErrorCodeType {
   /*
 	GROUPID  #17
 	MODULENAME = NVIC_SR101
   */

   /**
 	*ERRCODESTRING = NVIC_SR101_FUNC_ENTRY
 	*STRCODESTRING = Entered Function %s
   */
   NVIC_SR101_FUNC_ENTRY = 1U,
   /**
    * Exit specific function
    */

    /**
 	 *ERRCODESTRING = NVIC_SR101_FUNC_EXIT
 	 *STRCODESTRING = Exited Function %s
    */
   NVIC_SR101_FUNC_EXIT = 2U
   /*
 	ERRORCODEEND
   */

 }NVIC_SR101_ErrorCodeType;


 /**
  * @ingroup NVIC_SR101_publicparam
  * @{
  */
 /**
  * @brief Data structure which has the Channel Configuration options.
  * The channel selection and address configurations are done using
  * this structure.
  */

 typedef struct NVIC_SR101_SCUIntParamType
 {
	/**
	 * Callback Listener
	 */
   NVIC_SR101_CallbackType CbListener[NVIC_SR101_MAX]; /* User defined function*/
	/**
	 * Callback argument
	 */
   uint32_t CbArg[NVIC_SR101_MAX];
 }NVIC_SR101_SCUIntParamType;


 /**
  * @ingroup NVIC_SR101_publicparam
  * @{
  */
 typedef struct{
	/**
	 * SCU Parameter type
	 */
   NVIC_SR101_SCUIntParamType SCU[NVIC_SR101_MAX];
 }NVIC_SR101_HandleType;


 /**
  * @}
  */
 /*******************************************************************************
 **                      Global Constant Declarations                          **
 *******************************************************************************/


 /*******************************************************************************
 **                      Extern Variables                                      **
 *******************************************************************************/


 /*******************************************************************************
 ** FUNCTION PROTOTYPES                                                        **
 *******************************************************************************/

 /**
  * @ingroup NVIC_SR101_apidoc
  * @{
  */

 /**
  * @brief  Function to initialize the SCU.SR1 Event Masks based on  user configuration.
  *
  *
  * @param[in]  None
  *
  * @return     None
  *
  * <b>Reentrant: NO </b><BR>
  * <b>Sync/Async:  Synchronous</b>
  * @code
  *  #include <DAVE3.h>
  *
  *  int main(void)
  *  {
  *    DAVE_Init(); // NVIC_SR101_Init() is called within DAVE_Init()
  *    // .....
  *    return 0;
  *  }
  *
  * @endcode<BR> </p>
  */
 void  NVIC_SR101_Init(void);

 /**
   * @brief Function to Enable event handler functions for a specific SCU.SR1 Event. The
   *        user enables the event function and unmask the particular event bit.
   *
   * Service ID: 0x02
   *
   * @param[in]  Interrupt ID

   *
   * @return     None
   *
   * <b>Reentrant: NO </b><BR>
   * <b>Sync/Async:  Synchronous</b>
   * @code
   *  #include <DAVE3.h>
   *
   *
   *  int main(void)
   *  {
   *    DAVE_Init(); // NVIC_SR101_Init() is called within DAVE_Init()
   *    // Example usage of API
   *    NVIC_SR101_EnableEvent(NVIC_SR101_AI);
   *    // .....
   *    return 0;
   *  }
   *
   * @endcode<BR> </p>
   */
  void NVIC_SR101_EnableEvent(NVIC_SR101_InterruptType IntID);
  /**
    * @brief Function to disable event handler functions for a specific SCU.SR1 Event. The
    *        user enables the event function and mask the particular event bit.
    *
    * Service ID: 0x02
    *
    * @param[in]  Interrupt ID

    *
    * @return     None
    *
    * <b>Reentrant: NO </b><BR>
    * <b>Sync/Async:  Synchronous</b>
    * @code
    *  #include <DAVE3.h>
    *
    *
    *  int main(void)
    *  {
    *    DAVE_Init(); // NVIC_SR101_Init() is called within DAVE_Init()
    *    // Example usage of API
    *    NVIC_SR101_DisableEvent(NVIC_SR101_AI);
    *    // .....
    *    return 0;
    *  }
    *
    * @endcode<BR> </p>
    */
   void NVIC_SR101_DisableEvent(NVIC_SR101_InterruptType IntID);

 /**
  * @brief Function to register event handler functions for a specific SCU.SR1 Event. The
  *        user registers the callback function and if the event is unmasked,the Interrupt
  *        handler will service the Event as well as clear the Event Status Bit.
  *
  * Service ID: 0x02
  *
  * @param[in]  Interrupt ID
  * @param[in]  User defined Event Handler
  * @param[in]  Callback Function argument if any.
  *
  * @return     None
  *
  * <b>Reentrant: NO </b><BR>
  * <b>Sync/Async:  Synchronous</b>
  * @code
  *  #include <DAVE3.h>
  *
  *  void CbListener(uint32_t CbArg)
  *  {// Callback function implementation
  *  };
  *  int main(void)
  *  {
  *    DAVE_Init(); // NVIC_SR101_Init() is called within DAVE_Init()
  *    // Example usage of API
  *    NVIC_SR101_RegisterCallback(NVIC_SR101_AI,CbListener,0);
  *    // .....
  *    return 0;
  *  }
  *
  * @endcode<BR> </p>
  */
 NVIC_SR101_RegisterCbStatusType NVIC_SR101_RegisterCallback(
   NVIC_SR101_InterruptType IntID,
   NVIC_SR101_CallbackType userFunction,
   uint32_t CbArgs);

 /**
  *@}
  */

 #endif /* NVIC_SR101_H_ */

