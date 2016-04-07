# QR2matlab

This module sends to matlab the message coded in a QR code.
The visp_auto_tracker package reads the message of the QR code by a web cam and publishes the result as as a ROS Topic.

The QR2matlab subscribes to that topic and publishes the same message to matlab.

## Install

On the robot's computer :

sudo apt-get install ros-indigo-usb-cam
sudo apt-get install ros-indigo-visp-auto-tracker

roscd visp_auto_tracker/launch/
sudo nano tracklive_usb.launch

change the debug_display parameter to "False".


On the remote computer :

Install the QR2matlab

## Run

On the robot computer :

roslaunch visp_auto_tracker tracklive_usb.launch

On the remote computer :

genomixd & QR2matlab-ros & matlab &

and run the matlab script QR2matlab.m.

Now place a QR code in front of the robot's webcam and in remote matlab you will get the result.

