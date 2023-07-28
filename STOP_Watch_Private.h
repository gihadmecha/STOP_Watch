 


#ifndef STOP_WATCH_PRIVATE_H_
#define STOP_WATCH_PRIVATE_H_

#include "SEGMENTS.h"
#include "BUTTON.h"
#include "LED.h"
#include "BUZZER.h"

#define		PAUSE		0
#define		PLAY		1

#define		ADJUST_MODE		0
#define		WORKING_MODE	1

static void STOP_Watch_segments ();
static void STOP_Watch_increaseLeftSegment ();
static void STOP_Watch_increaseRightSegment ();
static void STOP_Watch_countingDown ();
static void STOP_Watch_reset ();
static void STOP_Watch_pause ();
static void STOP_Watch_pauseResume ();
static void STOP_watch_delay_s ();
static void STOP_Watch_workingMode ();
static void STOP_Watch_AdjustMode ();
static void STOP_Watch_switchMode ();



#endif /* STOP_WATCH_PRIVATE_H_ */