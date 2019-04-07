FROM ubuntu:18.04 
COPY . /usr/src/cliente 
WORKDIR /usr/src/cliente
RUN apt-get update \
    && apt-get install -y build-essential \
    && apt-get install -y iputils-ping \
    && apt-get install net-tools \
    && apt-get clean; rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /usr/share/doc/*
# docker network create
# docker network connect