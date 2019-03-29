# Hands-on Session ：MrBayes
MrBayes is a program for Bayesian inference and model choice across a wide range of phylogenetic and evolutionary models. MrBayes uses Markov chain Monte Carlo (MCMC) methods to estimate the posterior distribution of model parameters.

We will use MrBayes as an example to illustrate the use of build system.
```bash
# download source code
$ wget https://github.com/NBISweden/MrBayes/archive/v3.2.6.tar.gz

# prepare directory and go to source code directory
$ tar zxvf v3.2.6.tar.gz 
$ cd MrBayes-3.2.6
$ tar zxvf mrbayes-3.2.6.tar.gz && cd mrbayes-3.2.6/src

# load compiler and mpi library (use module load or manually add them to PATH and LD_LIBRARY_PATH)
$ module load GCC OpenMPI
```
Then take a look at `Makefile.in`.
```
# config the build
$ autoconf
```
Notice that 4 new files are generated, namely `autom4te.cache`(storing additional info for future use), `configure`(created by `autoconf`), `gpl.txt`(license), and `config.h.in`. Take a look at them, think about the relationship with help of the chart above.
```
$ mkdir install
$ ./configure --enable-mpi=yes --without-beagle --prefix=/path/to/your/MrBayes/install 

# build MrBayes in parallel. may also set a value to -j like -j8
$ make install -j
```