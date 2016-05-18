QR2matlab
========
This module sends to matlab the message coded in a QR code with the position and the orientation information.

The visp_auto_tracker package reads the message of the QR code by a web cam and publishes the result and the position + orientation information as two separate ROS Topic.

The QR2matlab subscribes to those topics and publishes the result in a single genom port.


#### 0. Dependencies :

ROS (Ingido) : http://wiki.ros.org/indigo/Installation/Ubuntu

GenoM3 : https://git.openrobots.org/projects/genom3

Matlab-genomix bridge : https://git.openrobots.org/projects/matlab-genomix

visp_auto_tracker : http://wiki.ros.org/visp_auto_tracker

#### 1. Install

- On the robot's computer :

```
> sudo apt-get install ros-indigo-usb-cam
> sudo apt-get install ros-indigo-visp-auto-tracker
```

You might want to disable the display and the printings on the terminal screen.

This is useful to block the transfert of the whole image to the remote computer.

```
> roscd visp_auto_tracker/launch/
> sudo nano tracklive_usb.launch
```

change the debug_display parameter to "False" and delete the output="screen" at ligne 16 and 26

And install the QR2matlab

```
> ./skeleton
> ./install
```

#### 2. Run

- On the robot computer :

```
> roscore &
> genomixd &
> roslaunch visp_auto_tracker tracklive_usb.launch &
> QR2matlab-ros &
```

- On the remote computer :

Open the matlab script QR2matlab.m
This script connects the ROS topics from visp_auto_tracker to the QR2matlab module and reads the QR2matlab/dataOut port.

#### 2. Output Information

The QR2matlab/dataOut genom port is published each 100 ms as following form :

```
geometry: 
  header: 
    seq: 1177
    stamp: 
      secs: 1463500806
      nsecs: 688076675
    frame_id: /map
  pose: 
    position: 
      x: 0.0862391498507
      y: 0.00555621400609
      z: 0.47812043592
    orientation: 
      x: 0.0159728032315
      y: 0.99915687111
      z: -0.0361875455902
      w: 0.0109944538213
message: 
  data: http://www.twoears.eu
```
