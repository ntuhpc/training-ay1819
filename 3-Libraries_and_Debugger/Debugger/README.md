# GNU Debugger - GDB

## Preparation 
Please read [this post](../reference/gdb-tutorial-handout.pdf) for an introduction to GDB.

## ex1 : find the bug


## Cheatsheet of common commands in GDB


### Breakpoint
* `b` - Put a breakpoint at the current line
* `b N` - Put a breakpoint at line N
* `b +N` - Put a breakpoint N lines down from the current line
* `b fn` - Put a breakpoint at the beginning of function "fn"
* `b main` - Put a breakpoint at the beginning of the program
* `info b` - list all breakpoints you have set
* `disable <breakpoint number>` - disable the specific breakpoint; similarly, you can `enable <breakpoint number>`


### Conditional Breakpoint
(gdb) break file1.c:6 if i >= ARRAYSIZE

* `d N` - delete breakpoint number N
* `info break` - list breakpoints

* `r` - Run the program until a breakpoint or error
* `c` - continue running the program until the next breakpoint or error

* `f` - Run until the current function is finished
* `s` - run the next line of the program, think of it as "step"
* `s N` - run the next N lines of the program
* `n` - like s, but don't step into functions

### Examine code
* `l <line number>` - list the surrounding code near `<line number>`
* `list<filename>:<line number>`  - list the surrounding code near `<line number>` in `<filename>`
* `list <function name>` - list the code of function

### Expression Evaluation
* `p var` - print the current value of the variable "var"
* `q` - Quit gdb

### Backtrace
* `backtrace` - used for looking at the stack of your program

## ex2 : find the logical bugs

### 1. Inner Product of two vectors

### 2. File I/O

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
[1] This sample code for ex2 is adopted from the [post](http://www.stat.purdue.edu/~liu105/STAT598G_lab/lab6.pdf). 

by [Dan Williams](http://www.pyrento.net/), and [GNU Build System](https://www.gnu.org/software/autoconf/manual/autoconf.html#The-GNU-Build-System).
