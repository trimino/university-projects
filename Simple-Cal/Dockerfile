FROM ubuntu:latest

# To run dkpg tools without interactive dialogue
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get install -y \
    cmake \
    build-essential \
    libgtk-3-dev \
    glade \
    git


RUN git clone https://github.com/trimino/simple_cal.git

WORKDIR /simple_cal

RUN chomd +x runme.sh

CMD ["/bin/bash"]
