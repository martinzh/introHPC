#!/bin/bash
#
# For more examples see:https://help.rc.ufl.edu/doc/Sample_SLURM_Scripts
#
#SBATCH --partition=gpu # request gpu partition
#
#SBATCH --job-name=test_matmul
#SBATCH -o slurm.%N.%j.out # STDOUT %N is the node, %j is the job
#SBATCH -e slurm.%N.%j.err # STDERR
#
#SBATCH --ntasks=56 # number of processes launched (number of MPI ranks)
#SBATCH --cpus-per-task=1 # Number of cores per mpi rank
#SBATCH --nodes=1 # number of nodes
#SBATCH --ntasks-per-node=1
##SBATCH --distribution=cyclic:cyclic # Distribute tasks cyclically on nodes and sockets
#
#SBATCH --time=0-0:1 # time format (D-HH:MM)
#SBATCH --mem-per-cpu=100 # request 100 MB per core
#

module load intel

# add here execution of your binaries  
