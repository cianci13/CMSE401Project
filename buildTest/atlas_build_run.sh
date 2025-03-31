#!/usr/bin/bash
#
# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
#
# This script is used during the build to set up a functional runtime
# environment for running scripts/executables.
#

# Transmit errors:
set -e

# Set up the environment:
source /msu/data/t3work13/dcianciolo/gepOutput2/gep/build/x86_64-slc7-gcc62-opt/setup.sh || exit 1

# Run the command:
exec $* || exit 1
