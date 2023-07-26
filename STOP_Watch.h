

#ifndef STOP_WATCH_H_
#define STOP_WATCH_H_

#include "StdTypes.h"
#include "SEGMENTS.h"
#include "BUTTON.h"

void STOP_Watch_segments ();
void STOP_Watch_increaseLeftSegment ();
void STOP_Watch_increaseRightSegment ();
void STOP_Watch_countingDown ();
void STOP_Watch_reset ();
void STOP_Watch_pause_resume ();
void STOP_watch_delay_s ();
void STOP_Watch_workingMode ();
void STOP_Watch_AdjustMode ();
void STOP_Watch_switchMode ();

#endif /* STOP_WATCH_H_ */