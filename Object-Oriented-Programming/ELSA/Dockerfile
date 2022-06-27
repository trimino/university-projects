FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

COPY . /ELSA/

RUN apt-get update -y && apt-get install -y \
    build-essential \
    libgtkmm-3.0-dev \
    papirus-icon-theme \
    libcanberra-gtk-module

WORKDIR /ELSA

RUN cd sprint4/src/ && make

CMD ["/bin/bash"]