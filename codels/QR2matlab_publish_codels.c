#include "acQR2matlab.h"

#include "QR2matlab_c_types.h"

#include <sys/time.h>
#include <string.h>
#include <stdio.h>

struct timeval tv;
static volatile uint32_t ii; 
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
  dataOut->write( self );
  return QR2matlab_ether;
}


/* --- Activity Publish ------------------------------------------------- */

/** Codel start of activity Publish.
 *
 * Triggered by QR2matlab_start.
 * Yields to QR2matlab_readQR.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
start(uint32_t bufferSize, QR2matlab_ids *ids, genom_context self)
{
  ids->data._length = bufferSize;
  if (genom_sequence_reserve(&(ids->data), bufferSize) )
	 return QR2matlab_e_noMemory( self );
	 
  int32_t iii;
  for ( iii = 0 ; iii < ids->data._length ; iii++ ) 
    strcpy(ids->data._buffer[iii], " ");

  ii = 0;
  return QR2matlab_readQR;
}

/** Codel readQR of activity Publish.
 *
 * Triggered by QR2matlab_readQR.
 * Yields to QR2matlab_pause_readQR, QR2matlab_writeQR.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
readQR(const QR2matlab_dataIn *dataIn, QR2matlab_ids *ids,
       genom_context self)
{
  dataIn->read(self);
  if(dataIn->data(self)->data != NULL)
	  strcpy(ids->data._buffer[ii], dataIn->data( self )->data);

  if (ii++ < ids->data._length-1 )
	  return QR2matlab_pause_readQR;
  else 
	  return QR2matlab_writeQR;
}

/** Codel writeQR of activity Publish.
 *
 * Triggered by QR2matlab_writeQR.
 * Yields to QR2matlab_ether.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
writeQR(const QR2matlab_ids *ids, const QR2matlab_dataOut *dataOut,
        genom_context self)
{
  dataOut->data(self)->message.data._length = ids->data._length;
  if ( genom_sequence_reserve(&(dataOut->data(self)->message.data), ids->data._length) )
	 return QR2matlab_e_noMemory( self );

  int32_t iii;      
  for ( iii = 0 ; iii < ids->data._length ; iii++ )
	if ( ids->data._buffer[iii] != NULL ) 
		strcpy(dataOut->data(self)->message.data._buffer[iii], ids->data._buffer[iii]);
		
  gettimeofday(&tv, NULL);
	 
  dataOut->data(self)->header.seq += 1;
  dataOut->data(self)->header.stamp.sec = tv.tv_sec;
  dataOut->data(self)->header.stamp.usec = tv.tv_usec;
		  
  dataOut->write( self );
  return QR2matlab_ether;
}

/** Codel stop of activity Publish.
 *
 * Triggered by QR2matlab_stop.
 * Yields to QR2matlab_ether.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
stop(QR2matlab_ids *ids, const QR2matlab_dataOut *dataOut,
     genom_context self)
{
  ids->data._release( ids->data._buffer );
  dataOut->data(self)->message.data._release( dataOut->data(self)->message.data._buffer );
  
  return QR2matlab_ether;
}
