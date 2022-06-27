#! /bin/bash


docker rm -f elsa

docker rmi -f elsa_build 

docker rmi $(docker images -f "dangling=true" -q)