#include "acQR2matlab.h"

#include "QR2matlab_c_types.h"

#include <sys/time.h>
#include <string.h>
#include <stdio.h>

struct timeval tv;

/* --- Task publish ----------------------------------------------------- */


/* --- Activity Publish ------------------------------------------------- */

/** Codel start of activity Publish.
 *
 * Triggered by QR2matlab_start.
 * Yields to QR2matlab_exec.
 */
genom_event
start(const QR2matlab_dataOut *dataOut, genom_context self)
{
  dataOut->data(self)->header.seq = 0;
  dataOut->write( self );
  return QR2matlab_exec;
}

/** Codel exec of activity Publish.
 *
 * Triggered by QR2matlab_exec.
 * Yields to QR2matlab_pause_exec, QR2matlab_stop.
 */
genom_event
exec(const QR2matlab_dataIn *dataIn, const QR2matlab_dataOut *dataOut,
     genom_context self)
{
  dataIn->read(self);
  if(dataIn->data(self)->data != NULL) {

	  gettimeofday(&tv, NULL);
	 
	  dataOut->data(self)->header.seq += 1;
	  dataOut->data(self)->header.stamp.sec = tv.tv_sec;
	  dataOut->data(self)->header.stamp.usec = tv.tv_usec;
		 
	  dataOut->data( self )->message.data = dataIn->data( self )->data ;
	  
	  dataOut->write( self );
  }
  return QR2matlab_pause_exec;
}

/** Codel stop of activity Publish.
 *
 * Triggered by QR2matlab_stop.
 * Yields to QR2matlab_ether.
 */
genom_event
stop(genom_context self)
{
  /* skeleton sample: insert your code */
  /* skeleton sample */ return QR2matlab_ether;
}
