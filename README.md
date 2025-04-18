This software is analysis tools for taking raw root data files from CERN and transforming them into TTrees so that one can access data, such as particle and detectors characteristics, for many events. This data can later be inputted to make histograms for data analysis in a wide variety of high-energy physics experiments at the LHC.

Software install (must be done pre gcc 3.15, so not the LHC)
- Clone the repo
- export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
- source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
- lsetup "root 6.34.04-x86_64-el9-gcc13-opt"

Copying the data files:
- cd gephistmaker
- cp /mnt/home/cianci13/CMSE401Project/gephistmaker/inputTree.root
- cp /mnt/home/cianci13/CMSE401Project/gephistmaker/inputTreeLarge.root

To change between serial and parallel, exchange plot_hists.c and RetrieveRecoEff.c with their stored serial versions, and vice versa.

Beyond the first install:
- export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
- source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
- lsetup "root 6.34.04-x86_64-el9-gcc13-opt"

Running (in CMSE401Project)
- set file paths to the paths to your input files, and the file you want to output to
- sbatch run.sb
- sbatch scalingStudy.sb

Or, cd gephistmaker and root new_hist_maker.c

To view plots, after setting up root, run root --web=off and new TBrowser()


