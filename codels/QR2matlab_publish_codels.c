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
init(QR2matlab_ids *ids, const QR2matlab_dataOut *dataOut,
     genom_context self)
{
  ids->data._length = 0;

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
start(int32_t bufferSize, QR2matlab_ids *ids, genom_context self)
{
  if ( ids->data._length != bufferSize ) {
	  ids->data._length = bufferSize;
	  if ( genom_sequence_reserve(&(ids->data), bufferSize) )
	  return QR2matlab_e_noMemory( self );
  }

  for ( int32_t iii = 0 ; iii < ids->data._length ; iii++ )
	ids->data._buffer[iii] = " ";
	  
  ii = 0;
  return QR2matlab_exec;
}

/** Codel readQR of activity Publish.
 *
 * Triggered by QR2matlab_exec.
 * Yields to QR2matlab_pause_exec, QR2matlab_publish.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
readQR(const QR2matlab_dataIn *dataIn, QR2matlab_ids *ids,
       genom_context self)
{
  dataIn->read(self);
  
  if ( dataIn->data(self)->data != NULL )  {
		ids->data._buffer[ii] = dataIn->data( self )->data;
  }
  
  ii++;
  if ( ii < ids->data._length )
	return QR2matlab_pause_exec;
  else	  
    return QR2matlab_publish;
}

/** Codel writeQR of activity Publish.
 *
 * Triggered by QR2matlab_publish.
 * Yields to QR2matlab_ether.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
writeQR(QR2matlab_ids *ids, const QR2matlab_dataOut *dataOut,
        genom_context self)
{
  for ( int32_t iii = 0 ; iii < ids->data._length ; iii++ )
	printf("%d - % s", iii, ids->data._buffer[iii]);
		
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
  // dataOut->data(self)->message.data._release( dataOut->data(self)->message.data._buffer );
  return QR2matlab_ether;
}
