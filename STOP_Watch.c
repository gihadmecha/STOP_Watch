
#include "STOP_Watch.h"
#include "STOP_Watch_Private.h"
#include "BUZZER.h"

static u8 leftSegment = 0;
static u8 rightSegment = 0;

static u8 setLeftSegment = 0;
static u8 setRightSegment = 0;

static u8 pausePlayFlag = PAUSE;

static u8 modeFlag = WORKING_MODE; 


extern void STOP_Watch_Init ()
{
	DIO_Init();
}

static void STOP_Watch_segments ()
{
	u8 number = leftSegment * 10 + rightSegment;
	SEGMENTS_STOP_Watch (number);
}

static void STOP_Watch_increaseLeftSegment ()
{
	leftSegment++;
	
	if (leftSegment == 10)
	{
		leftSegment = 0;
	}
	
	setLeftSegment = leftSegment;
}

static void STOP_Watch_increaseRightSegment ()
{
	rightSegment++;
	
	if (rightSegment == 10)
	{
		rightSegment = 0;
	}
	
	setRightSegment = rightSegment;
}

static void STOP_Watch_pause ()
{
	pausePlayFlag = PAUSE;
	LED1_Off();
}

static void STOP_Watch_pauseResume ()
{
	pausePlayFlag = !pausePlayFlag;
	
	if (pausePlayFlag == PAUSE)
	{
		LED1_Off();
	}
}

static void STOP_Watch_reset ()
{
	leftSegment = setLeftSegment;
	rightSegment = setRightSegment;
	STOP_Watch_pause ();
}

static void STOP_Watch_switchMode ()
{
	modeFlag = !modeFlag;
}

static void STOP_watch_delay_s ()
{
	for (u32 index = 0; index < 250 && modeFlag == WORKING_MODE; index++)
	{
		// 4 mSec delay
		STOP_Watch_segments ();
		//needed to check periodically
		BUTTON1_IfPressed_PeriodicCheck (STOP_Watch_pauseResume);
		BUTTON2_IfPressed_PeriodicCheck (STOP_Watch_reset);
		BUTTON_mode_IfPressed_PeriodicCheck (STOP_Watch_switchMode);
	}
}

static void STOP_Watch_countingDown ()
{
	static u8 currentNumber;
	
	static u8 oneFlag = 0;
	
	if (pausePlayFlag == PLAY && modeFlag == WORKING_MODE)
	{
		currentNumber = leftSegment * 10 + rightSegment;
		
		if (currentNumber != 0)
		{
			LED1_On();
			
			currentNumber--;
			
			leftSegment = currentNumber / 10;
			rightSegment = currentNumber % 10;
			
			if (currentNumber == 1)
			{
				oneFlag = 1;
			}
		}
		else
		{
			LED1_Off();
			
			if (oneFlag == 1)
			{
				oneFlag = 0;
				
				BUZZER_On();
				STOP_watch_delay_s ();
				BUZZER_Off();
			}
		}
	}
}

static void STOP_Watch_workingMode ()
{
		STOP_watch_delay_s ();
		STOP_Watch_countingDown ();
}

static void STOP_Watch_AdjustMode ()
{
		LED1_Off();
		STOP_Watch_pause ();
		STOP_Watch_segments ();
		//needed to check periodically
		BUTTON1_IfPressed_PeriodicCheck (STOP_Watch_increaseLeftSegment);
		BUTTON2_IfPressed_PeriodicCheck (STOP_Watch_increaseRightSegment);
		BUTTON_mode_IfPressed_PeriodicCheck (STOP_Watch_switchMode);
}

extern void STOP_Watch_run ()
{
	if (modeFlag == WORKING_MODE)
	{
		STOP_Watch_workingMode ();
	}
	else if (modeFlag == ADJUST_MODE)
	{
		STOP_Watch_AdjustMode ();
	}
}
