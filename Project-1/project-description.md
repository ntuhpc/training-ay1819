# Overview

This project consists of 3 assignments. Each assignment will have one team member as helper. It is designed to be completed by a team of 4-6 members. Checkpointing will be used to help you complete the project.

## Assignment 1 : Learn to use OpenMP (30 pts)

In this assignment, you are going to refresh your OpenMP knowledge with some practices. 

* Learn from the slides by Tim Mattson : https://www.openmp.org/wp-content/uploads/Intro_To_OpenMP_Mattson.pdf
* Think of an task can be parallelized. Implement your algorithm, and try to re-write using OpenMP.

The helper is *Hao Meiru*.

## Assignment 2 : Parallel Floyd-Warshall Algorithm (30 pts)

The [Floyd–Warshall algorithm](https://en.wikipedia.org/wiki/Floyd–Warshall_algorithm) is an algorithm for finding shortest paths in a weighted graph. Due to cubic time complexity of this algorithm, it desirable to optimize it through parallelization. An guided report on FW algorithm and it's OpenMP implementation can be found at https://gkaracha.github.io/papers/floyd-warshall.pdf (you only need to focus on OpenMP part of the report).

In this assignment, you are going to :

* generate a random adjacency matrix to represent the graph
* implement FW algorithm (`Floyd_Warshall_ST`)
* implemebt FW algorithm with OpenMP (`Floyd_Warshall_OpenMP`)
* using the same adj matrix, compare the CPU time of `Floyd_Warshall_OpenMP` against `Floyd_Warshall_ST`.

Starter code can be found in `2.Floyd`.

The helpers are *Shen Youlin and Shi Ziji*.

## Assignment 3 : Weather Research and Forecast (40 pts)

You are asked to benchmark the Weather Research and Forecasting (WRF) Model. WRF is the next-generation mesoscale numerical weather prediction system, designed to serve both operational forecasting and atmospheric research needs. More info can be found at: https://www.mmm.ucar.edu/weather-research-and-forecasting-model

The code for WRF v3.9.1.1 can be obtained from: http://www2.mmm.ucar.edu/wrf/users/download/get_sources.html.

You are asked to demonstrates the highest performance and scalability utilizing the NSCC cluster based on the standard WRF 2.5km CONUS benchmark for WRF (http://www2.mmm.ucar.edu/WG2bench/conus_2.5_v3/). Teams can use any MPI library of their choice (OpenMPI, MVAPICH, HPC-X etc.).

You should build WRF according to the instructions provided with the program using one of the `dmpar` options of the configuration script.  The resulting configure.wrf file may be edited before compiling, to make any needed adjustments for the MPI version used.  To execute the program, the restart and boundary data files need to be downloaded and rebuilt according to steps 1 (a), (b), (d) and (e) of http://www2.mmm.ucar.edu/WG2bench/conus_2.5_v3/READ-ME.txt . The namelist.input file to be used is under `3.WRF`, since the namelist.input file mentioned in step 1(c) of the above READ-ME.txt file is not valid for recent versions of WRF.

The measure of performance will be the Simulation Speed, which is computed by means of the stats.awk script as follows:

```sh
% grep ’Timing for main’ rsl.error.0000 | tail -1439 | awk ’{print $9}’ | awk -f stats.awk
```

Some suggestions: 
> The main difficulty with WRF is in its compilation. It depends on a lot of external libraries. Therefore, it is recommend to build it in a iterative approach. You compile the necessary libraries first, then link with optimiation libraries like MKL, compile with Intel Compiler etc.

The helper is *Zhang Xinye*.

## Checkpoint

Checkpointing is a bi-weekly general meeting for all teams. This is to ensure everything is going in the right direction, and team can use it to ask questions & clear puzzles. It is recommended that one member per team should be present per checkpoint meeting.

We have planned 3 check points dates.

* Dec 15, 2018
* Dec 29, 2018
* Jan 12, 2018

Ideally, all questions should be asked in respective Slack channels, and checkpointing meetings are used to understand the progress of each team.

## Communications

Please send all questions to respective channels on Slack. If you found any issues/bugs with the code, you can start an issue in this repo.

# Project Submission

The deadline of this project is the Sunday of Week 1, Semester 2. (Jan 20, 2019)

To submit, you should compress everything you have done (including `stats.awk` for WRF), upload to a online drive, and share the link with Shi Ziji.