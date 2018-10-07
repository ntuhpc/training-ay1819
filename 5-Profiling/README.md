# Overview

[Arm](https://www.arm.com) Forge is a suite of tools including Arm DDT and Arm MAP. Arm DDT is the industry-leading parallel debugger supporting MPI, CUDA, and OpenMP. Arm MAP is the low-overhead line-level profiler for MPI, OpenMP, and scalar programs.

- [Download Arm Forge (DDT + MAP)](https://www.Arm.com/products/forge/download)
- [Arm Forge Userguide](https://developer.arm.com/docs/101136/latest/arm-forge/introduction)

 
# Installation

Arm only supports profiling on Linux platforms. There are remote clients on Linux/macOS/Windows for remote connection to Linux servers. For the licence, place it under `/path/to/Arm/installation/licences`.

> The licence only need to be placed on the actual Linux server performing the profiling. Remote clients will read licence information after connecting to the remote server. NSCC has a license that covers all educational institutions in Singapore so you don't need to purchase it.


# Connecting to a remote server

When using the remote client, configure the remote server for connection.

- Hostname: The syntax is `[username]@hostname[:port]`. To login via one or more intermediate hosts, enter the host names in order separated by spaces (e.g. `gateway.Arm.com cluster.lan`).
- Remote installation directory: Full path to Arm Forge on the remote system.
- Remote script: An optional script to be run before starting the remote daemon on the remote system. You may write environment variables to a script and set this to the scripts's path. 
- Load Profile Data File: You can also run map profiler using command line and without using GUI, then scp the result to local and use GUI version to view.
<!-- Always look for source files locally: Use source files on local system instead of the remote system.-->

# Preparing a program for profiling

- Debugging symbols: Compile your program with the debug flag (usually `-g`, and remove `-DNDEBUG`). **Also keep optimization flags turned on!**
<!--- Linking: MAP uses two small profiler libraries, `map-sampler` and `map-sampler-mpi`. On most systems MAP can do this automatically (via the `LD_PRELOAD` mechanism).
	- This automatic linking only works if the program is dynamically-linked
	- If automatic linking fails
		- Try linking your code dynamically
		- Link MAP's libraries manually at link time
		- Recompile MPI with `--enable-dynamic`-->

# Profiling a program

Set settings accordingly in the run window, then hit `Run` to start the profiling.

# Profiling result

This section explains how to interpret the results obtained after a profile run.

## Source code view

Shows profiling statistics for each line of the source code (if at least 0.1% time was spent on a line). MPI code has three colors:

- **Dark green**: single-threaded computation time.
- **Blue**: MPI communication and waiting time.
- **Orange**: I/O time.
- **Dark purple**: Accelerator.

> Any triangular patterns in graph shows imbalance. Those areas should be investigated.

### OpenMP programs

In OpenMP programs, you also see these colors:

- **Light green**: Multi-threaded computation time.
- **Light blue**: Multi-threaded MPI communication time.
- **Dark grey**: Time inside an OpenMP region in which a core is idle or waiting to synchronize with the other OpenMP threads.
- **Pale blue**: Thread synchronization time.

## Selected lines view

This view can be accessed by highlighting a line in the code viewer. Multiple lines can be selected. The panel is divided into two sections:

- The first section gives an overview of how much time was spent executing instructions on this line, and how much time was spent in other functions.
- The second section details the CPU instruction metrics for the selected line.

> In general, aim for a large proportion of time in vector operations.

## Stacks view

The stacks view offers a good top-down view of your program. Each line of the stacks view shows the performance of one line of your source code. Clicking on any line of the stacks view jumps the source code view to show that line of code.

## OpenMP regions view

The OpenMP regions view gives insight into the performance of every significant OpenMP region in the program. Each region can be expanded just as in the stacks view.

## Functions view

The functions view shows a flat profile of the functions in the program.

- **Self** shows the time spent in code in the given function itself, but not its callees
- **Total** shows the time spent in code in the given function itself, and all its callees
- **Child** shows the time spent in the given functions's callees only.

## Project files view

The project files view offers a great way to browse around and navigate through a large, unfamiliar code base. It distinguishes between application code and external code. External code is typically system libraries that are hidden away at startup.

## Metrics view

By default three metrics graphs are shown. The top-most is the main thread activity chart.

All of the other metric graphs show how single numerical measurements vary across processes and time. Initially, two frequently used ones are shown: CPU floating-point and memory usage. Each vertical slice of a graph shows the distribution of values across processes for that moment in time.

> A thin line means all processes had very similar values; a fat shaded region means there is significant imbalance between the processes.

Click the Metrics button to choose one of the following presets or any combination of the metrics beneath them.

### CPU instructions

- CPU floating-point: The percentage of time each rank spends in floating-point CPU instructions. This includes vectorized / SIMD instructions and standard x87 floating-point.
- CPU integer: The percentage of time each rank spends in integer CPU instructions. This includes vectorized/SIMD instructions and standard integer operations.
- CPU memory access: The percentage of time each rank spends in memory access CPU instructions, such as move, load and store. This also includes vectorized memory access functions. **Extremely high values (98% and above) almost always indicate cache problems.**
- CPU floating-point vector: The percentage of time each rank spends in vectorized/SIMD floating-point instructions.
- CPU integer vector: The percentage of time each rank spends in vectorized/SIMD integer instructions.
- CPU branch: The percentage of time each rank spends in test and branch-related instructions such as `test`, `cmp` and `je`.

### CPU time

- CPU time: The percentage of time that each thread of your program was able to spend on a core. **This is a key indicator of oversubscription or inteference from system daemons.**
- User-mode CPU time: The percentage of time spent executing instructions in user-mode.
- Kernel-mode CPU time: The percentage of time spent executing instructions in system calls to the kernel.
- Voluntary context switches: Number of times per second that a thread voluntarily slept (e.g. when waiting for an I/O call to complete)
- Involuntary context switches The number of times per second that a thread was interrupted while computing and switched out for another one. **This will happen if the the cores are oversubscribed, or if other system processes and daemons start running and take CPU resources away from your program.**
- System load The number of active (running or runnable) threads as a percentage of the number of physical CPU cores present in the compute node.

### I/O

- Disk read transfer: The rate at which the application reads data from disk, in bytes per second.
- Disk write transfer: The rate at which the application writes data to disk, in bytes per second.

### Memory

- Memory usage: The current RAM usage of each process. **Memory allocated and never used is generally not shown. (i.e. called malloc but never initialized the memory)**
- Node memory usage: The percentage of each nodes' memory that is in use at any one time.

### MPI

- MPI call duration: This metric tracks the time spent in an MPI call so far.
- MPI sent/received: This pair of metrics tracks the number of bytes passed to MPI send/receive functions per second.
- MPI point-to-point/collective operations: This pair of metrics tracks the number of point-to-point/collective calls per second.
- MPI point-to-point/collective bytes: This pair of metrics tracks the number of bytes passed to MPI send/receive functions per second.

# Performance Report 

Performance report is super easy to read and provides an intuitive idea before using Allinea MAP. It also doesn't required to be recompiled with `-g` flag. 

- [Arm Performance Report User Guide](https://www.osc.edu/sites/default/files/documentation/userguide-reports.pdf)
- [Arm Performance Report Video Tutorial](https://developer.arm.com/products/software-development-tools/hpc/arm-performance-reports/video-demos-and-tutorials)

## Example
```bash
module load arm/reports/18.0
#export Arm_NO_TIMEOUT=1 #disable timeout, because perf-report needs long time to initialise.
perf-report mpirun -n 2 helloworld
```

There will be a html and a txt file generated in the same folder. From your laptop, copy the html from NSCC to your laptop by using `scp haom0001@ntu.nscc.sg:/path/to/your/html/example.html .`
<!--Performance Reports can be used to summarize an application profile generated by Arm MAP. To produce
a performance report from an exisiting MAP output file called profile.map, simply run:
`perf-report profile.map`-->


# Hands-on : MrBayes

## Get MrBayes

```bash
$ cd 5-Profiling/
$ wget https://github.com/NBISweden/MrBayes/archive/v3.2.6.tar.gz

$ tar zxvf v3.2.6.tar.gz 
$ cd MrBayes-3.2.6
$ tar zxvf mrbayes-3.2.6.tar.gz && cd mrbayes-3.2.6
$ mkdir install && cd src

$ module load intelcc intelmpi

$ autoconf
$ ./configure --enable-mpi=yes --without-beagle --prefix=/path/to/your/MrBayes/install CC=mpiicc CXX=icpc
```

## Compile in debug mode

Change the CFLAG in `Makefile` to allow debug info to be exposed to profiler:

```bash
CFLAGS       = -O3  -DUSECONFIG_H -g
```

then, compile MrBayes by:

```bash
$ make -j
$ make install
```
## Edit input file

Change `your-username` in line 3 of `5-Profiling/mb_input.nex`

## Start Arm Forge Client on your laptop

![Alt text](./screenshot/remote-launch.jpg?raw=true "Remote Launch Window")

* *Remote Installation Directory*: The full path to the Arm Forge installation on the remote system.
* *Remote Script*: This optional script will be run before starting the remote daemon on the remote system. You may use this script to load the required modules for DDT and MAP, your MPI and compiler. See the following sections for more details. The script is usually not necessary when using Reverse Connect.

* *Always look for source files locally*: Check this box to use the source files on the local system instead of the remote system.

## Get profiling report

### Method 1 : Use Reverse Connect

First, send an interactive job request of desired time slot (see previous posts).
Then,

```bash
$ module load intelmpi arm/forge/18.0
$ map --connect mpirun -n 12  ~/path/to/your/bin/mb ~/training-ay1819/5-Profiling/mb_input.nex
```
Accept the request on your MAP client.

### Method 2 : Use .map file generated with `map`

First, send an interactive job request of desired time slot (see previous posts).
Then, 

```bash
$ module load intelmpi arm/forge/18.0
$ map --profile  mpirun -n 12  ~/path/to/your/bin/mb ~/training-ay1819/5-Profiling/mb_input.nex
```
Open the generated `.map` file on your MAP client.

### Method 3: Use remote job script

Please refer to `./job.sub` and Arm Forge manual.
> Remember to change `PBS_O_WORKDIR` in line 8 of job.sub
