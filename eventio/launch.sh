#!/bin/sh

gcc --std=c99 -o client_weight client_weight_thread.c
./client_weight $2 10 100
