# Hipsters_In_Swarm

[![Build Status](https://www.travis-ci.com/AmeyaWagh/Hipsters_In_Swarm.svg?branch=master)](https://www.travis-ci.com/AmeyaWagh/Hipsters_In_Swarm)

<p align="left"> 
 <a href="https://github.com/AmeyaWagh/Hipsters_In_Swarm/blob/devel/LICENSE" alt="Contributors">
        <img src="https://img.shields.io/apm/l/vim-mode.svg?style=popout" /></a>
</p>


[![IMAGE ALT TEXT HERE](assets/hipsters_in_swarm.gif)]()


In the social networks like Facebook, Twitter, or
Instagram the spread of opinions, memes, news or in the network
of people the spread of diseases or rumors depends on its structure
as well as the spreading process. However, heterogeneous
behavior among different type of agents can substantially change
this spreading dynamics. For example, anti-establishment nodes
also known as hipsters can significantly affect the spreading
dynamics of two competing products when only one product was
present initially. Here, we aim to investigate such behavior in the
Swarm of Robots by introducing hipster robots in the network.


A complete project report can be found [here](assets/Swarm_Intelligence_final_project_report.pdf).

---

## Installation

### Install ARGoS

- For (16.04) https://drive.google.com/file/d/1Mi8r9xOF4Nror7zTtoOZcILDE10AujjB/view 
- For (18.04) https://drive.google.com/file/d/1VGDogC8tBipOv2kykJH4hsckXoBRKmFa/view 

Install using dpkg
```bash
sudo dpkg -i argos3_simulator-3.0.0-i686-beta53.deb
```

To verify installation, run test
```bash
argos3 -q all
```

### Install Buzz
```bash
git clone https://github.com/NESTLab/Buzz.git buzz
cd buzz
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../src
make
sudo make install
sudo ldconfig
```

### Install Khepera IV Robot sim
```bash
git clone https://github.com/ilpincy/argos3-kheperaiv.git
cd argos3-kheperaiv
mkdir build_sim
cd build_sim
cmake -DCMAKE_BUILD_TYPE=Release ../src
make
sudo make install
```

### Download Hipsters_In_Swarm
```bash
git clone https://github.com/AmeyaWagh/Hipsters_In_Swarm
```

---

### Compiling the Hipster_In_Swarm code
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Running the Hipster_In_Swarm script
Go to project directory and run
```bash
./test.sh
```

### Running the Experiments
Go to project directory and run
```bash
./run_experiments.sh
```
