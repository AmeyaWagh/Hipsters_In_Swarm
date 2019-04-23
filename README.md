# Hipsters_In_Swarm


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
cd argos-kheperaiv
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
