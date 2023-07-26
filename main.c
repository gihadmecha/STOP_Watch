
#include "DIO_interface.h"
#include "SEGMENTS.h"
#include "BUTTON.h"
#include "STOP_Watch.h"

int main ()
{
	DIO_Init();
	
	SEGMENTS_left(0);
	SEGMENTS_right(0);
	
	u8 leftSegment;
	u8 rightSegment;
	
	while (1)
	{
		//Working Mode
		
		
		
		//Adjust Mode
		leftSegment = BUTTON1_IfPressed_PeriodicCheck (increaseLeftSegment);
		if (leftSegment != BUTTON1_NOT_PRESSED)
		{
			SEGMENTS_left(leftSegment);
		}
		
		rightSegment = BUTTON2_IfPressed_PeriodicCheck (increaseRightSegment);
		if (rightSegment != BUTTON2_NOT_PRESSED)
		{
			SEGMENTS_right(rightSegment);
		}
	}
	
}

