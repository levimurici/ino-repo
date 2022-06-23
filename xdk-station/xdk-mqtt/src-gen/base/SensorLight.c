/**
 * Generated by Eclipse Mita 0.1.0.
 * @date 2021-09-13 13:23:51
 */


#include <BCDS_Basics.h>
#include <BCDS_Retcode.h>
#include <BCDS_LightSensor.h>
#include <XdkSensorHandle.h>
#include "MitaExceptions.h"


Retcode_T SensorLight_Setup(void)
{
	Retcode_T exception = RETCODE_OK;
	
	exception = LightSensor_init(xdkLightSensor_MAX44009_Handle);
	if(exception != NO_EXCEPTION) return exception;
	
	// Configure manual mode
	exception = LightSensor_setManualMode(xdkLightSensor_MAX44009_Handle, LIGHTSENSOR_MAX44009_DISABLE_MODE);
	if(exception != NO_EXCEPTION) return exception;
	
	/*
	 * Integration time and high-brightness are automatically choosen by the sensor because manual mode is disabled.
	 */
	// exception = LightSensor_setBrightness(xdkLightSensor_MAX44009_Handle, LIGHTSENSOR_NORMAL_BRIGHTNESS);
	// if(exception != NO_EXCEPTION) return exception;
	// exception = LightSensor_setIntegrationTime(xdkLightSensor_MAX44009_Handle, LIGHTSENSOR_800_MS);
	// if(exception != NO_EXCEPTION) return exception;
	
	// Configure continuous mode
	exception = LightSensor_setContinuousMode(xdkLightSensor_MAX44009_Handle, LIGHTSENSOR_MAX44009_DISABLE_MODE);
	if(exception != NO_EXCEPTION) return exception;
	
	return NO_EXCEPTION;
}

Retcode_T SensorLight_Enable(void)
{
	
	return NO_EXCEPTION;
}

