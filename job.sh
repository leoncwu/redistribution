#!/bin/bash
#SBATCH -J redistricting3   # job name
#SBATCH -o out.o%j         # output and error file name (%j expands to jobID)
#SBATCH -N 1               # Total # of nodes
#SBATCH -n 1              # total number of mpi tasks requested
#SBATCH -p skx-normal    # queue (partition) -- normal, development, etc.
#SBATCH -t 11:59:00        # run time (hh:mm:ss) - 1.5 hours
#SBATCH -A sds335      # Project name
#SBATCH --mail-user=chunlin_wu@utexas.edu
#SBATCH --mail-type=begin  # email me when the job starts
#SBATCH --mail-type=end    # email me when the job finishes

export OMP_NUM_THREADS=48
#ibrun --membind=1 ./vort_sol<param.inp ./out.log  # run the MPI executable named a.out
./redistricting<param.inp ./out.log
