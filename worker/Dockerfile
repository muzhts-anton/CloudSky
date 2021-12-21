FROM ubuntu:20.04
MAINTAINER CoDex
# RUN  apt-get update \
#   && apt-get install -y wget \
#   && rm -rf /var/lib/apt/lists/*
# RUN apt-get install manpages-dev
# RUN wget https://github.com/protocolbuffers/protobuf/releases/download/v3.19.1/protobuf-cpp-3.19.1.tar.gz
# RUN tar -xf protobuf-cpp-3.19.1.tar.gz
# RUN ls
# RUN ./protobuf-3.19.1/configure
# RUN make
# RUN make check
# RUN make install
# RUN ldconfig
# Try 1
# RUN echo "include /usr/local/llb/*" > /etc/ld.so.conf
# RUN ldconfig
# Try 2
# RUN touch /etc/ld.so.conf.d/protobuf.conf
# RUN echo "/usr/local/llb" > /etc/ld.so.conf.d/protobuf.conf
# RUN ldconfig
# Try 3
# RUN echo "/usr/local/llb" > /etc/ld.so.conf.d/libc.conf
# RUN ldconfig

# ARG DEBIAN_FRONTEND=noninteractive
# RUN apt-get -yq install apt-utils

# ubuntu:latest does not have sudo
# fetch it and install it
RUN apt-get update && apt-get install -y sudo

# Create new user `docker` and disable 
# password and gecos for later
# --gecos explained well here:
# https://askubuntu.com/a/1195288/635348
RUN adduser --disabled-password \
--gecos '' docker

#  Add new user docker to sudo group
RUN adduser docker sudo

# Ensure sudo group users are not 
# asked for a password when using 
# sudo command by ammending sudoers file
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> \
/etc/sudoers

# now we can set USER to the 
# user we just created
USER docker

# we can now run sudo commands 
# as non-root user `docker` without
# password prompt
RUN sudo apt-get update 


#RUN apt-get install dialog apt-utils
# sudo
# RUN apt-get update && \ 
#       apt-get -y install sudo

#RUN useradd -m docker && echo "docker:docker" | chpasswd && adduser docker sudo
#sudo
COPY /usr/local/lib/libprotobuf.so.30 /
COPY /usr/local/lib/libprotobuf.so.30 /usr/local/lib/

RUN  sudo sh -c "echo '/usr/local/lib' >> /etc/ld.so.conf"
#RUN sudo echo "/usr/local/llb" > /etc/ld.so.conf.d/libc.conf
#sudo
RUN  sudo ldconfig

ENV DEBIAN_FRONTEND newt


COPY build/CloudSky_MyWorker /
COPY build/fileToSend.bin /
ENV PORT "8050"
ENV IP "127.0.0.1"
CMD sudo LD_LIBRARY_PATH=/usr/local/lib/libprotobuf.so.30 ./CloudSky_MyWorker $PORT $IP 