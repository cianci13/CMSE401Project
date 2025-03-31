This software is analysis tools for taking raw root data files from CERN and transforming them into TTrees so that one can access data, such as particle and detectors characteristics, for many events. This data can later be inputted to make histograms for data analysis in a wide variety of high-energy physics experiments at the LHC.

Software install (must be done pre gcc 3.15, so not the LHC)
- Clone the repo
- export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
- source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
- cd build
- acmSetup Athena,21.9,latest
- cd ../source
- acm add_pkg athena/Trigger/TrigL0GepPerf
- acm compile

Copying the data file:
- cd ../run
- cp /mnt/home/cianci13/AOD.26811025._000007.pool.root.1 ./

Beyond the first install:
- cd build
- acmSetup
- acm compile

Then:
- cd ../run
- athena GepJobOptions.py

Alternatively, sbatch run.sb


