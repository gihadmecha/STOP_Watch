
#include "STOP_Watch.h"

static u8 leftSegment = 0;
static u8 rightSegment = 0;

static u8 setLeftSegment = 0;
static u8 setRightSegment = 0;

//pause
static u8 pause_resume_flag = 0;

//working mode
static u8 modeFlag = 1; 

static u8 resetFlag = 0;


void STOP_Watch_segments ()
{
	SEGMENTS_left(leftSegment);
	SEGMENTS_right(rightSegment);
}

void STOP_Watch_increaseLeftSegment ()
{
	leftSegment++;
	
	if (leftSegment == 10)
	{
		leftSegment = 0;
	}
	
	setLeftSegment = leftSegment;
}

void STOP_Watch_increaseRightSegment ()
{
	rightSegment++;
	
	if (rightSegment == 10)
	{
		rightSegment = 0;
	}
	
	setRightSegment = rightSegment;
}

void STOP_Watch_countingDown ()
{
	static u8 currentNumber;
	
	if (pause_resume_flag == 1)
	{
		currentNumber = leftSegment * 10 + rightSegment;
		
		if (currentNumber != 0)
		{
			currentNumber--;
			
			leftSegment = currentNumber / 10;
			rightSegment = currentNumber % 10;
		}
	}
}

void STOP_Watch_reset ()
{
	leftSegment = setLeftSegment;
	rightSegment = setRightSegment;
	//pause
	pause_resume_flag = 0;
	resetFlag = 1;
}

void STOP_Watch_pause_resume ()
{
	pause_resume_flag = !pause_resume_flag;
}

void STOP_watch_delay_s ()
{
	for (u32 index = 0; index < 100000 && modeFlag == 1 && resetFlag == 0; index++)
	{
		BUTTON1_IfPressed_PeriodicCheck (STOP_Watch_pause_resume);
		BUTTON2_IfPressed_PeriodicCheck (STOP_Watch_reset);
		BUTTON_mode_IfPressed_PeriodicCheck (STOP_Watch_switchMode);
		_delay_us(10);
	}
}

void STOP_Watch_workingMode ()
{
	if (modeFlag == 1)
	{
		STOP_watch_delay_s ();
		
		if (resetFlag == 0)
		{
			STOP_Watch_countingDown ();
		}
		
		resetFlag = 0;
	}
}

void STOP_Watch_AdjustMode ()
{
	if (modeFlag == 0)
	{
		BUTTON1_IfPressed_PeriodicCheck (STOP_Watch_increaseLeftSegment);
		BUTTON2_IfPressed_PeriodicCheck (STOP_Watch_increaseRightSegment);
		BUTTON_mode_IfPressed_PeriodicCheck (STOP_Watch_switchMode);
	}
}

void STOP_Watch_switchMode ()
{
	DIO_TogglePin(PIND0);
	modeFlag = !modeFlag;
}
//
//void STOP_Watch_runMode ()
//{
	//if (modeFlag == 1)
	//{
		//STOP_Watch_workingMode ();
	//}
	//else if (modeFlag == 0)
	//{
		//STOP_Watch_AdjustMode ();
	//}
//}