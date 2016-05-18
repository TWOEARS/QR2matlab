#include "acQR2matlab.h"

#include "QR2matlab_c_types.h"

#include <string.h>
#include <stdio.h>

static volatile uint32_t ii;

/* --- Task publish ----------------------------------------------------- */

/* --- Activity Publish ------------------------------------------------- */

/** Codel start of activity Publish.
 *
 * Triggered by QR2matlab_start.
 * Yields to QR2matlab_pause_start.
 * Throws QR2matlab_e_noMemory, QR2matlab_e_noData.
 */
genom_event
start(const QR2matlab_messageIn *messageIn,
      const QR2matlab_poseIn *poseIn, const QR2matlab_dataOut *dataOut,
      genom_context self)
{
  messageIn->read(self);
  poseIn->read(self);
  if ( (messageIn->data(self) == NULL) || (poseIn->data(self) == NULL) )
	return QR2matlab_e_noData( self );

  dataOut->data( self )->geometry.header.seq = poseIn->data( self )->header.seq;
  dataOut->data( self )->geometry.header.stamp.sec = poseIn->data( self )->header.stamp.sec;	  
  dataOut->data( self )->geometry.header.stamp.nsec = poseIn->data( self )->header.stamp.nsec;
  dataOut->data( self )->geometry.header.frame_id = poseIn->data( self )->header.frame_id; 

  dataOut->data( self )->geometry.pose.position.x = poseIn->data( self )->pose.position.x;
  dataOut->data( self )->geometry.pose.position.y = poseIn->data( self )->pose.position.y;	  
  dataOut->data( self )->geometry.pose.position.z = poseIn->data( self )->pose.position.z;

  dataOut->data( self )->geometry.pose.orientation.x = poseIn->data( self )->pose.orientation.x;
  dataOut->data( self )->geometry.pose.orientation.y = poseIn->data( self )->pose.orientation.y;	  
  dataOut->data( self )->geometry.pose.orientation.z = poseIn->data( self )->pose.orientation.z;
  dataOut->data( self )->geometry.pose.orientation.w = poseIn->data( self )->pose.orientation.w; 
	  	  	  
  dataOut->data( self )->message.data = messageIn->data( self )->data;
  
  dataOut->write( self );

  return QR2matlab_pause_start;
}

/** Codel stop of activity Publish.
 *
 * Triggered by QR2matlab_stop.
 * Yields to QR2matlab_ether.
 * Throws QR2matlab_e_noMemory, QR2matlab_e_noData.
 */
genom_event
stop(genom_context self)
{
  return QR2matlab_ether;
}
