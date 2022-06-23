/**
 * Generated by Eclipse Mita 0.1.0.
 * @date 2021-09-13 13:23:51
 */


#include <BCDS_Basics.h>
#include <BSP_BoardType.h>
#include <MitaEvents.h>
#include <BCDS_BSP_Button.h>
#include <BCDS_CmdProcessor.h>
#include <BCDS_Retcode.h>
#include "MitaExceptions.h"

void ButtonOne_OnEvent(uint32_t data)
{
	if(data == BSP_XDK_BUTTON_PRESS) {
		Retcode_T retcode = CmdProcessor_enqueueFromIsr(&Mita_EventQueue, HandleEveryButton_onePressed1, NULL, data);
		if(retcode != RETCODE_OK)
		{
			Retcode_RaiseErrorFromIsr(retcode);
		}
	}
}


Retcode_T SensorButton_one_Setup(void)
{
	return BSP_Button_Connect();
	
	return NO_EXCEPTION;
}

Retcode_T SensorButton_one_Enable(void)
{
	Retcode_T retcode = NO_EXCEPTION;
	
	retcode = BSP_Button_Enable((uint32_t) BSP_XDK_BUTTON_1, ButtonOne_OnEvent);
	if(retcode != NO_EXCEPTION) return retcode;
	
	return NO_EXCEPTION;
}


