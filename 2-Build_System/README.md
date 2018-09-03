# Introduction
Build systems are software tools designed to automate the process of program compilation. Some commonly used build systems include:
* make
* CMake
* configure
* scons

# Build System Philosophy
At their core, build systems are a functional based languages mapping a set of source resources (in most cases, files) to a target (executable). The primary assumption of the build system is _each invocation of a build command with the same input and options will create the same output_. This assumption *allows the build system to memoize the actions that is has already performed, and only perform build actions on resources that have changed*.

# Popular Build Systems
For most modern build systems, practicality beats out most other concerns. This section describes some of the popular build systems in use today, along with the code for building the simple example described above. Note, the examples below don't necessarily have the exact same functionality, especially with regard to dependency tracking. Rather, they are the simples versions of the given tool that successfully compiled the hello world program.

## Make
[Make](http://www.gnu.org/software/make/) is one of the original build systems, coming out of Bell Labs. Currently the most popular incarnation of Make is GNU Make. Make allows for explicit mapping between source and target (foo.o: foo.c), as well as general mappings (%.o: %.c). Make also allows for "phony" target, which where the command executed does not actually create the target. This allows Makefiles to perform additional functionality. Further, the GNU extensions to make allow it to be highly customizable, making it able to perform much of the deployment configuration usually reserved to configure.Here is the simple hello example in GNU Make:

```bash
OBJS=hello.o hello_io.o
CC=gcc

hello: $(OBJS)
    $(CC) -o $@ $(OBJS)

%.o: %.c
    $(CC) -c $<
```

## Scons

[Scons](https://www.scons.org/) is a python-based build tool, focusing on flexibility and scripting. Scons SConstruct files are interpreted as python scripts. Here is the hello build in Scons:

```python
env = Environment()
env.Program(target="hello", source=["hello.c", "hello_io.c"])
Scons is focused on flexibility and platform independence, and the cost of performance. Because scons is based on a general-purpose language it offers a wide range of extensible features, including custom builders and file scanning.
```
## CMake
[CMake](https://cmake.org/) is "cross platform make." It is designed with portability in mind. CMake specifics dependencies in it's own configuration file, which is then used to create "native" makefile in the target environment. Here is the CMakeLists.txt for the example:

```cmake
add_executable (hello hello.c hello_io.c)
```

## Configure
## Autogen

# Preparation
1. Login to NSCC with NTU account
2. Submit an interactive job request of 1h with 12 CPU cores
```bash
# this command may take a while
$ qsub -I -l select=1:ncpus=12 -P personal -l walltime=01:00:00
```
3. After the job starts, issue the following commands *if you do have a copy of this repo on NSCC* (otherwise, go to step 4):
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


# Acknowledgement
This tutorial is based on the [post](https://www.cs.virginia.edu/~dww4s/articles/build_systems.html) by [Dan Williams](http://www.pyrento.net/). 
