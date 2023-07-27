

#ifndef STOP_WATCH_H_
#define STOP_WATCH_H_

#include "SEGMENTS.h"
#include "BUTTON.h"
#include "LED.h"

#define		PAUSE		0
#define		PLAY		1

#define		ADJUST_MODE		0
#define		WORKING_MODE	1


extern void STOP_Watch_Init ();
extern void STOP_Watch_run ();

#endif /* STOP_WATCH_H_ */