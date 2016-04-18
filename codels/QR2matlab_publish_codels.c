#include "acQR2matlab.h"

#include "QR2matlab_c_types.h"

#include <sys/time.h>
#include <string.h>
#include <stdio.h>

struct timeval tv;
static volatile int32_t ii;
/* --- Task publish ----------------------------------------------------- */


/** Codel init of task publish.
 *
 * Triggered by QR2matlab_start.
 * Yields to QR2matlab_ether.
 */
genom_event
init(const QR2matlab_dataOut *dataOut, genom_context self)
{
  dataOut->data(self)->header.seq = 0;
  dataOut->data(self)->message.data._length = 0;

  dataOut->write( self );

  return QR2matlab_ether;
}


/* --- Activity Publish ------------------------------------------------- */

/** Codel start of activity Publish.
 *
 * Triggered by QR2matlab_start.
 * Yields to QR2matlab_exec.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
start(int32_t bufferSize, const QR2matlab_dataOut *dataOut,
      genom_context self)
{
  if ( dataOut->data(self)->message.data._length != bufferSize ) {
	  dataOut->data(self)->message.data._length = bufferSize;
	  if (genom_sequence_reserve(&(dataOut->data(self)->message.data), bufferSize) )
	  return QR2matlab_e_noMemory( self );
  }

  for ( int32_t iii = 0 ; iii < bufferSize ; iii++ )
    dataOut->data( self )->message.data._buffer[ii] = "Not seen any QRcode";

  dataOut->write( self );
  ii = 0;

  return QR2matlab_exec;
}

/** Codel exec of activity Publish.
 *
 * Triggered by QR2matlab_exec.
 * Yields to QR2matlab_pause_exec, QR2matlab_ether.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
exec(const QR2matlab_dataIn *dataIn,
     const QR2matlab_dataOut *dataOut, genom_context self)
{
  dataIn->read(self);
  if(dataIn->data(self)->data != NULL) {
		
	  if ( ii < dataOut->data(self)->message.data._length ) {
		if ( !( strcmp(dataIn->data( self )->data, "") ) )
		  	dataOut->data( self )->message.data._buffer[ii] = dataIn->data( self )->data;
		else
		  	dataOut->data( self )->message.data._buffer[ii] = "Not seen any QRcode";
		ii++;
		return QR2matlab_pause_exec;
	  }

 	  ii = 0;
	  dataOut->write( self );
	  gettimeofday(&tv, NULL);
		 
	  dataOut->data(self)->header.seq += 1;
	  dataOut->data(self)->header.stamp.sec = tv.tv_sec;
	  dataOut->data(self)->header.stamp.usec = tv.tv_usec;
  }
  return QR2matlab_ether;
}

/** Codel stop of activity Publish.
 *
 * Triggered by QR2matlab_stop.
 * Yields to QR2matlab_ether.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
stop(const QR2matlab_dataOut *dataOut, genom_context self)
{
  dataOut->data(self)->message.data._release( dataOut->data(self)->message.data._buffer );
  return QR2matlab_ether;
}
