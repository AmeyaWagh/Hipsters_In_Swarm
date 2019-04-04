#!/bin/bash

# Author: Ameya Wagh
# email: aywagh@wpi.edu

if [ ! -d "$DIRECTORY" ]; then
  mkdir results
fi

argos3 -c experiments/hipsters_in_network.argos