#! /bin/bash

docker build -t calc_build ../


echo '-e DISPLAY =$DISPLAY: Passing the data to the x11 socket'
echo '-v /tmp/.X11-unix:/tmp/.X11-unix: Makes the x11 unix domain socket available in the container'

echo 'Chaning the default x11 settings to allow all users to print'
xhost +


docker run -it --name calc -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix calc_build