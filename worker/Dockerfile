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
COPY build/CloudSky_MyWorker /
COPY build/fileToSend.bin /
ENV PORT "8050"
ENV IP "127.0.0.1"
CMD ./CloudSky_MyWorker $PORT $IP