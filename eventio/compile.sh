#!/bin/sh

gcc --std=c99 -o server server.c
gcc --std=c99 -o client client.c
gcc --std=c99 -o client_weight client_weight.c
