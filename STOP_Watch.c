
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
	u8 number = leftSegment * 10 + rightSegment;
	SEGMENTS_STOP_Watch (number);
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

void STOP_Watch_pause ()
{
	pause_resume_flag = 0;
	DIO_WritePin(PINC1, LOW);
}

void STOP_Watch_pause_resume ()
{
	pause_resume_flag = !pause_resume_flag;
	
	if (pause_resume_flag == 0)
	{
		DIO_WritePin(PINC1, LOW);
	}
}

void STOP_Watch_reset ()
{
	leftSegment = setLeftSegment;
	rightSegment = setRightSegment;
	//pause
	STOP_Watch_pause ();
	resetFlag = 1;
}

void STOP_watch_delay_s ()
{
	for (u32 index = 0; index < 250 && modeFlag == 1 && resetFlag == 0; index++)
	{
		BUTTON1_IfPressed_PeriodicCheck (STOP_Watch_pause_resume);
		BUTTON2_IfPressed_PeriodicCheck (STOP_Watch_reset);
		BUTTON_mode_IfPressed_PeriodicCheck (STOP_Watch_switchMode);
		STOP_Watch_segments ();
	}
}

void STOP_Watch_countingDown ()
{
	static u8 currentNumber;
	
	static u8 oneFlag = 0;
	
	if (pause_resume_flag == 1)
	{
		currentNumber = leftSegment * 10 + rightSegment;
		
		if (currentNumber != 0)
		{
			DIO_WritePin(PINC1, HIGH);
			
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
			DIO_WritePin(PINC1, LOW);
			
			if (oneFlag == 1)
			{
				oneFlag = 0;
				
				DIO_TogglePin(PINC5);
				STOP_watch_delay_s ();
				DIO_TogglePin(PINC5);
			}
		}
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
		DIO_WritePin(PINC1, LOW);
		STOP_Watch_pause ();
		BUTTON1_IfPressed_PeriodicCheck (STOP_Watch_increaseLeftSegment);
		BUTTON2_IfPressed_PeriodicCheck (STOP_Watch_increaseRightSegment);
		BUTTON_mode_IfPressed_PeriodicCheck (STOP_Watch_switchMode);
		STOP_Watch_segments ();
	}
}

void STOP_Watch_switchMode ()
{
	modeFlag = !modeFlag;
}
