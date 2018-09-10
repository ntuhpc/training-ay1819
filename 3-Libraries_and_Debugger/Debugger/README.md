# GNU Debugger - GDB

## ex1 : find the bug


## Cheatsheet of common commands 

* `b` - Put a breakpoint at the current line
* `b N` - Put a breakpoint at line N
* `b +N` - Put a breakpoint N lines down from the current line
* `b fn` - Put a breakpoint at the beginning of function "fn"
* `b main` - Put a breakpoint at the beginning of the program

* `d N` - delete breakpoint number N
* `info break` - list breakpoints

* `r` - Run the program until a breakpoint or error
* `c` - continue running the program until the next breakpoint or error

* `f` - Run until the current function is finished
* `s` - run the next line of the program, think of it as "step"
* `s N` - run the next N lines of the program

* `n` - like s, but don't step into functions
* `p var` - print the current value of the variable "var"
* `q` - Quit gdb

## ex2 : find the logical bugs

# Preparation
1. Login to NSCC with NTU account
2. Submit an interactive job request of 2h with 4 CPU cores
```bash
# this command may take a while
$ qsub -I -l select=1:ncpus=4 -P personal -l walltime=2:00:00
```
3. After the job starts, issue the following commands *if you do have a copy of this repo on NSCC* (otherwise, go to step 4):
```bash
# ssh into nscc04 
$ ssh nscc04-ib0
$ git clone https://github.com/ntuhpc/training-ay1819.git
```
4. Go to directory for this workshop
```bash
$ cd 3-Libraries_and_Debugger
```

# Hands-on Session ：

# Acknowledgement
This tutorial is partially adopted from the [post](https://www.cs.virginia.edu/~dww4s/articles/build_systems.html) by [Dan Williams](http://www.pyrento.net/), and [GNU Build System](https://www.gnu.org/software/autoconf/manual/autoconf.html#The-GNU-Build-System).
