
#include "DIO_interface.h"
#include "SEGMENTS.h"
#include "BUTTON.h"
#include "STOP_Watch.h"

int main ()
{
	DIO_Init();
	
	while (1)
	{
		STOP_Watch_segments ();
		STOP_Watch_workingMode ();
		STOP_Watch_AdjustMode ();
	}
	
}

