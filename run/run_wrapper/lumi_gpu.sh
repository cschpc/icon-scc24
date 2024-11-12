#!/bin/bash

# ICON
#
# ------------------------------------------
# Copyright (C) 2004-2024, DWD, MPI-M, DKRZ, KIT, ETH, MeteoSwiss
# Contact information: icon-model.org
# See AUTHORS.TXT for a list of authors
# See LICENSES/ for license information
# SPDX-License-Identifier: BSD-3-Clause
# ------------------------------------------

while getopts n:o:e: argv
do
    case "${argv}" in
        n) mpi_total_procs=${OPTARG};;
        o) io_tasks=${OPTARG};;
        e) executable=${OPTARG};;
    esac
done

set -eu
(( compute_tasks = mpi_total_procs - io_tasks ))

if (( SLURM_PROCID < compute_tasks ))
then

    echo Compute process $SLURM_LOCALID on $(hostname)

    device=$(($SLURM_LOCALID%8))

    export ROCR_VISIBLE_DEVICES=$device

else

    echo IO process $SLURM_LOCALID on $(hostname)

fi
exec $executable
