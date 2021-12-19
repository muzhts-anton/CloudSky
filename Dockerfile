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
# RUN export LD_LIBRARY_PATH=/usr/local/lib
# RUN mkdir docker_worker/
RUN apt-get update && apt-get -y install cmake protobuf-compiler
COPY worker/ docker_worker/
RUN cd docker_worker/build
RUN cmake .. 
RUN make
#COPY build/CloudSky_MyWorker /
ENV PORT "8050"
ENV IP "127.0.0.1"
CMD LD_LIBRARY_PATH=/usr/local/lib/libprotobuf.so.30 ./CloudSky_MyWorker $PORT $IP