
#include "STOP_Watch.h"

static u8 leftSegment = 0;
static u8 rightSegment = 0;

void countingDown ()
{
	
}

u8 increaseLeftSegment ()
{
	leftSegment++;
	
	if (leftSegment == 10)
	{
		leftSegment = 0;
	}
	
	return leftSegment;
}

u8 increaseRightSegment ()
{
	rightSegment++;
	
	if (rightSegment == 10)
	{
		rightSegment = 0;
	}
	
	return rightSegment;
}