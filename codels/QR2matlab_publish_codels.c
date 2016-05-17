#include "acQR2matlab.h"

#include "QR2matlab_c_types.h"

#include <sys/time.h>
#include <string.h>
#include <stdio.h>

static volatile uint32_t ii;

/* --- Task publish ----------------------------------------------------- */

/* --- Activity Publish ------------------------------------------------- */

/** Codel start of activity Publish.
 *
 * Triggered by QR2matlab_start.
 * Yields to QR2matlab_readQR.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
start(uint32_t bufferSize, QR2matlab_QR2matlab_Struct_Seq *dataOut,
      genom_context self)
{
  if (genom_sequence_reserve(&(dataOut->info), bufferSize) )
	 return QR2matlab_e_noMemory( self );
	 
  dataOut->info._length = bufferSize;
  	 
  uint32_t iii;
  for ( iii = 0 ; iii < dataOut->info._length ; iii++ ) 
    strcpy(dataOut->info._buffer[iii].message.data, " ");

  ii = 0;
  return QR2matlab_readQR;
}

/** Codel readQR of activity Publish.
 *
 * Triggered by QR2matlab_readQR.
 * Yields to QR2matlab_pause_readQR, QR2matlab_ether.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
readQR(const QR2matlab_messageIn *messageIn,
       const QR2matlab_poseIn *poseIn,
       QR2matlab_QR2matlab_Struct_Seq *dataOut, genom_context self)
{
  messageIn->read(self);
  poseIn->read(self);
  if ( (messageIn->data(self) != NULL) && (poseIn->data(self) != NULL) ) {
	  
	  dataOut->info._buffer[ii].geometry.header.seq = poseIn->data( self )->header.seq;
	  dataOut->info._buffer[ii].geometry.header.stamp.sec = poseIn->data( self )->header.stamp.sec;	  
	  dataOut->info._buffer[ii].geometry.header.stamp.nsec = poseIn->data( self )->header.stamp.nsec;
	  dataOut->info._buffer[ii].geometry.header.frame_id = poseIn->data( self )->header.frame_id; 

	  dataOut->info._buffer[ii].geometry.pose.position.x = poseIn->data( self )->pose.position.x;
	  dataOut->info._buffer[ii].geometry.pose.position.y = poseIn->data( self )->pose.position.y;	  
	  dataOut->info._buffer[ii].geometry.pose.position.z = poseIn->data( self )->pose.position.z;

	  dataOut->info._buffer[ii].geometry.pose.orientation.x = poseIn->data( self )->pose.orientation.x;
	  dataOut->info._buffer[ii].geometry.pose.orientation.y = poseIn->data( self )->pose.orientation.y;	  
	  dataOut->info._buffer[ii].geometry.pose.orientation.z = poseIn->data( self )->pose.orientation.z;
	  dataOut->info._buffer[ii].geometry.pose.orientation.w = poseIn->data( self )->pose.orientation.w; 
	  	  	  
	  strcpy(dataOut->info._buffer[ii].message.data, messageIn->data( self )->data);
  }

  if (ii++ < dataOut->info._length-1 )
	  return QR2matlab_pause_readQR;
  else 
	  return QR2matlab_ether;
}

/** Codel stop of activity Publish.
 *
 * Triggered by QR2matlab_stop.
 * Yields to QR2matlab_ether.
 * Throws QR2matlab_e_noMemory.
 */
genom_event
stop(QR2matlab_QR2matlab_Struct_Seq *dataOut, genom_context self)
{
  // ids->data._release( ids->data._buffer );
  // dataOut->data(self)->message.data._release( dataOut->data(self)->message.data._buffer );

  return QR2matlab_ether;
}
