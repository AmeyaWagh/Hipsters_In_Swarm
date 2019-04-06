#!/bin/bash

# Author: Ameya Wagh
# email: aywagh@wpi.edu

N_ROBOTS=(10 20 30 40 50) # can go upto 50 
HIPSTER_PERCENTAGE=(5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100)


function create_result_dir(){
  # create result dir
  if [ ! -d "results" ]; then
    mkdir results
  fi
}

function create_simulation(){
  n_robots=$1
  h_percentage=$2
  out_file="results/trial_nRobot${n_robots}_hPerc${h_percentage}.txt" 

  # create simulation file from template
  sed -e "s|N_ROBOTS|${n_robots}|" -e "s|OUT_FILE|${out_file}|" -e "s|HIPSTER_PERCENTAGE|${h_percentage}|" experiments/hipsters_in_network_exp.argos > demo.argos

  # run experiment
  argos3 -c demo.argos

  #clean-up
  rm demo.argos
}


#----------------------------------------------#
# Main                                         #
#----------------------------------------------#
create_result_dir

for n_robots_ in ${N_ROBOTS[*]}
do
    for h_percent_ in ${HIPSTER_PERCENTAGE[*]}
    do 
      echo "Running simulation with $n_robots_ and hipster percentage of $h_percent_"
      create_simulation $n_robots_ $h_percent_
    done
done