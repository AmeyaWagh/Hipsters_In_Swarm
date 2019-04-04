#!/bin/bash

if [ ! -d "$DIRECTORY" ]; then
  mkdir results
fi

argos3 -c experiments/hipsters_in_network.argos