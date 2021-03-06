#!/bin/bash

mkdir SimulatorFiles
cd SimulatorFiles

# install qt5
sudo apt update -y
sudo apt install -y qtbase5-dev
sudo apt install -y lua5.2
sudo apt install -y freeglut3-dev 

#----------------- ARGOS -------------------------------#
# Download argos3
echo "Downloading Argos3"
fileid="1Mi8r9xOF4Nror7zTtoOZcILDE10AujjB"
filename="argos3.deb"
curl -c ./cookie -s -L "https://drive.google.com/uc?export=download&id=${fileid}" > /dev/null
curl -Lb ./cookie "https://drive.google.com/uc?export=download&confirm=`awk '/download/ {print $NF}' ./cookie`&id=${fileid}" -o ${filename}

echo "Installing Argos3"
sudo dpkg -i argos3.deb

sudo apt install -f
echo "Verify Installation of Argos3"
argos3 -q all

#----------------- Buzz -------------------------------#
git clone https://github.com/NESTLab/Buzz.git buzz
cd buzz
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../src
make
sudo make install
sudo ldconfig
echo "export BUZZ_INCLUDE_PATH=/usr/local/share/buzz" >> ~/.bashrc
cd ../../
#----------------- Khepera IV Robot Simulator -------------------------------#
git clone https://github.com/ilpincy/argos3-kheperaiv.git
cd argos3-kheperaiv
mkdir build_sim
cd build_sim
cmake -DCMAKE_BUILD_TYPE=Release ../src
make
sudo make install
#----------------- Hipsters_In_Swarm -------------------------------#
cd ../../
# mkdir build
# cd build
# cmake -DCMAKE_BUILD_TYPE=Release ..
# make
