#!/bin/bash

# Author: Ameya Wagh
# email: aywagh@wpi.edu

N_ROBOTS=50
OUT_FILE="results/trail_n${N_ROBOTS}.txt" 

if [ ! -d "results" ]; then
  mkdir results
fi

sed -e "s|N_ROBOTS|${N_ROBOTS}|" -e "s|OUT_FILE|${OUT_FILE}|" experiments/hipsters_in_network_exp.argos > demo.argos
argos3 -c demo.argos
rm demo.argos