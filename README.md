# QR2matlab

## Install

On the robot computer :

sudo apt-get install ros-indigo-usb-cam
sudo apt-get install ros-indigo-visp-auto-tracker

On the remote computer :

Install the QR2matlab

## Run

On the robot computer :

roslaunch visp_auto_tracker tracklive_usb.launch

On the remote computer :

genomixd & QR2matlab-ros & matlab &

and run the matlab script QR2matlab.m.

Place a QR code in front of the robot's webcam and in matlab you will get the result.

