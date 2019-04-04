#!/bin/bash

# Author: Ameya Wagh
# email: aywagh@wpi.edu

N_ROBOTS=50
HIPSTER_PERCENTAGE=40
OUT_FILE="results/trail_nRobot${N_ROBOTS}_hPerc${HIPSTER_PERCENTAGE}.txt" 

# create result dir
if [ ! -d "results" ]; then
  mkdir results
fi

# create simulation file from template
sed -e "s|N_ROBOTS|${N_ROBOTS}|" -e "s|OUT_FILE|${OUT_FILE}|" -e "s|HIPSTER_PERCENTAGE|${HIPSTER_PERCENTAGE}|" experiments/hipsters_in_network_exp.argos > demo.argos

# run experiment
argos3 -c demo.argos

#clean-up
rm demo.argos