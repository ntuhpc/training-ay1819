# Introduction
Build systems are software tools designed to automate the process of program compilation. Some commonly used build systems include:
* make
* CMake
* configure
* scons

# Preparation
1. Login to NSCC with NTU account
2. Submit an interactive job request of 1h with 12 CPU cores
```bash
# this command may take a while
$ qsub -I -l select=1:ncpus=12 -P personal -l walltime=01:00:00
```
3. After the job starts, issue the following commands *if you do have a copy of this repo on NSCC*:
```bash
# ssh into nscc04 
$ ssh nscc04-ib0
$ git clone https://github.com/StevenShi-23/NTU-HPC-Training-AY18-19.git
```
4. Go to directory for this workshop
```bash
$ cd 2-Build_System
```

# Content
MrBayes is a program for Bayesian inference and model choice across a wide range of phylogenetic and evolutionary models. MrBayes uses Markov chain Monte Carlo (MCMC) methods to estimate the posterior distribution of model parameters.

We will use MrBayes as an example to illustrate the use of build system.
```bash
# download source code
$ wget https://github.com/NBISweden/MrBayes/archive/v3.2.6.tar.gz
# prepare directory
$ tar zxvf v3.2.6.tar.gz && cd MrBayes-3.2.6
$ tar zxvf mrbayes-3.2.6.tar.gz && cd mrbayes-3.2.6/src

# config the build
$ autoconf
$ ./configure --enable-mpi=yes --with-beagle=/path/to/just/above/beagle-lib --prefix=/path/to/your/MrBayes CC=mpiicc CXX=icpc
# build MrBayes in parallel. Can also set a value to -j like -j8
$ make install -j
```
