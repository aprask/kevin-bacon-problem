#!/bin/bash
#SBATCH --job-name=bacon
#SBATCH --partition=Centaurus
#SBATCH --time=05:30:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --mem=256G
./run_4.sh

