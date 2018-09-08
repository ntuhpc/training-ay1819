# Introduction
Build systems are software tools designed to automate the process of program compilation. Some commonly used build systems include:
* make
* CMake
* configure
* scons

# Build System Philosophy
At their core, build systems are a functional based languages mapping a set of source resources (in most cases, files) to a target (executable). The primary assumption of the build system is _each invocation of a build command with the same input and options will create the same output_. This assumption allows the build system to *memoize the actions that is has already performed, and only perform build actions on resources that have changed*.

# How Build System Figures Out Dependencies
For a build system to correctly do partial rebuilds of only the components that have changed, it must fully understand the dependencies of the build. Generally, there are two methods to specify the dependencies: implicitly or explicitly. 

## Explicit dependencies 
Explicit dependencies are the most straight forward to implement, the relationship is explicitly encoded in the build script. Most build systems have the ability to explicitly specify a dependency, even if they try to find the majority of dependencies implicitly.

### Example : Makefile
```Makefile
edit : main.o kbd.o command.o display.o \
       insert.o search.o files.o utils.o
        cc -o edit main.o kbd.o command.o display.o \
                   insert.o search.o files.o utils.o

main.o : main.c defs.h
        cc -c main.c
kbd.o : kbd.c defs.h command.h
        cc -c kbd.c
command.o : command.c defs.h command.h
        cc -c command.c
display.o : display.c defs.h buffer.h
        cc -c display.c
insert.o : insert.c defs.h buffer.h
        cc -c insert.c
search.o : search.c defs.h buffer.h
        cc -c search.c
files.o : files.c defs.h buffer.h command.h
        cc -c files.c
utils.o : utils.c defs.h
        cc -c utils.c
clean :
        rm edit main.o kbd.o command.o display.o \
           insert.o search.o files.o utils.o
```

Also see our ISC'17 application miniDFT's [makefile](https://github.com/ntuhpc/isc17-minidft/blob/master/src/Makefile.cpu).

## Implicit Dependencies
Build systems find implicit dependencies a number of ways. First is by file association. Most build tools use common file extensions to identify file types. So, given the file `hello.c` many build systems will infer a build dependency from `hello.c` to `hello.o`. 

Further, additional dependencies can be inferred from contents of the file. The build system can scan the `.c` file for `#include` directives, and then add a new dependency from associated header file to the source file. This technique does not always work, however, because include directives can be [guarded by the preprocessor](https://en.wikipedia.org/wiki/Include_guard). In general it is undecidable to discover whether a source file will actually include a given header.

### Example : CMake
CMake is a system to generate make files based on the platform (i.e. CMake is cross platform) which you can then `make` using the generated makefiles.

```CMake
MAKE_DEPENDENT_OPTION(NEKTAR_SOLVER_ADR
    "Build the ADR Solver." ON
    "NEKTAR_BUILD_SOLVERS" OFF)

IF (NOT NEKTAR_BUILD_SOLVERS)
    SET(NEKTAR_SOLVER_ADR OFF CACHE INTERNAL "")
ENDIF()

IF( NEKTAR_SOLVER_ADR )
    ADD_SOLVER_EXECUTABLE(ADRSolver SOURCES
        ./ADRSolver.cpp 
        ./EquationSystems/Helmholtz.cpp
        ./EquationSystems/Laplace.cpp
        ./EquationSystems/Poisson.cpp
        ./EquationSystems/Projection.cpp

...

```
Example taken from ISC'18 application [Nektar++](https://gitlab.nektar.info/nektar/nektar/blob/master/solvers/ADRSolver/CMakeLists.txt).

# Popular Build Systems
Here comes some examples:

## Make
[Make](http://www.gnu.org/software/make/) allows for explicit mapping between source and target (foo.o: foo.c), as well as general mappings (%.o: %.c). Make also allows for "phony" target, which where the command executed does not actually create the target. This allows Makefiles to perform additional functionality. Here is the simple hello example in GNU Make:

```bash
OBJS=hello.o hello_io.o
CC=gcc

hello: $(OBJS)
    $(CC) -o $@ $(OBJS)

%.o: %.c
    $(CC) -c $<
```

## Scons

[Scons](https://www.scons.org/) is a *python-based* build tool, focusing on flexibility and scripting. Scons SConstruct files are interpreted as python scripts. Here is the hello build in Scons:

```python
env = Environment()
env.Program(target="hello", source=["hello.c", "hello_io.c"])
```
Scons is focused on flexibility and platform independence, and the cost of performance. Because scons is based on a general-purpose language it offers a wide range of extensible features, including custom builders and file scanning.

## CMake
[CMake](https://cmake.org/) is "cross platform make." CMake specifics dependencies in it's own configuration file, which is then used to create "native" makefile in the target environment. Here is the `CMakeLists.txt` for the example:

```cmake
add_executable (hello hello.c hello_io.c)
```

## Autogen
[Autoconf](https://www.gnu.org/software/autoconf/manual/autoconf.html) is a tool for producing shell scripts that *automatically configure software source code packages* to adapt to many kinds of Posix-like systems. The configuration scripts produced by Autoconf are independent of Autoconf when they are run, so their *users do not need to have Autoconf*.

The configuration scripts that Autoconf produces are by convention called `configure`. When run, `configure` creates several files, replacing configuration parameters in them with appropriate values.

### Example : PETsc
```bash
./configure --with-blas-lib=/path/to/BLAS/lib/libopenblas.a \
    --with-lapack-lib=/path/to/lapack/lib/libscalapack.a \
    --with-cc=mpicc --with-cxx=mpicxx --with-fc=mpif90
```

# Flow Diagram of GNU Build System
![alt text](https://upload.wikimedia.org/wikipedia/commons/8/84/Autoconf-automake-process.svg)


# Preparation
1. Login to NSCC with NTU account
2. Submit an interactive job request of 1.5h with 12 CPU cores
```bash
# this command may take a while
$ qsub -I -l select=1:ncpus=12 -P personal -l walltime=01:30:00
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

# Hands-on Session ： MrBayes
MrBayes is a program for Bayesian inference and model choice across a wide range of phylogenetic and evolutionary models. MrBayes uses Markov chain Monte Carlo (MCMC) methods to estimate the posterior distribution of model parameters.

We will use MrBayes as an example to illustrate the use of build system.
```bash
# download source code
$ wget https://github.com/NBISweden/MrBayes/archive/v3.2.6.tar.gz

# prepare directory and go to source code directory
$ tar zxvf v3.2.6.tar.gz 
$ cd MrBayes-3.2.6
$ tar zxvf mrbayes-3.2.6.tar.gz && cd mrbayes-3.2.6/src

# load intel compiler and mpi library
$ module load intelcc intelmpi
```
Then take a look at `Makefile.in`.
```
# config the build
$ autoconf
```
Notice that 4 new files are generated, namely `autom4te.cache`(storing additional info for future use), `configure`(created by `autoconf`), `gpl.txt`(license), and `config.h.in`. Take a look at them, think about the relationship with help of the chart above before proceeding.
```
$ mkdir install
$ ./configure --enable-mpi=yes --without-beagle --prefix=/path/to/your/MrBayes/install CC=mpiicc CXX=icpc

# build MrBayes in parallel. may also set a value to -j like -j8
$ make install -j
```


# Acknowledgement
This tutorial is partially adopted from the [post](https://www.cs.virginia.edu/~dww4s/articles/build_systems.html) by [Dan Williams](http://www.pyrento.net/), and [GNU Build System](https://www.gnu.org/software/autoconf/manual/autoconf.html#The-GNU-Build-System).
