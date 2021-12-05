FROM ubuntu:20.04
MAINTAINER CoDex
COPY build/CloudSky_MyWorker /
COPY build/fileToSend.bin /
ENV PORT "8050"
ENV IP "127.0.0.1"
CMD ./CloudSky_MyWorker $PORT $IP