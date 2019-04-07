FROM ubuntu:18.04 
COPY . /usr/src/servidor
WORKDIR /usr/src/servidor
RUN apt-get update \
    && apt-get install -y build-essential \
    && apt-get install -y iputils-ping \
    && apt-get install net-tools \
    && apt-get clean; rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /usr/share/doc/*
# docker network create
# docker network connect
