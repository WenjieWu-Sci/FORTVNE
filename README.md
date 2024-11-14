# FORTVNE
Simulation code for R&D of the FORward TeV Neutrino Experiment (FORTVNE), inherited from [FLArE's code](https://github.com/WenjieWu-Sci/FLArE).

## Setting up on lxplus
The `LXPLUS` service at CERN (`lxplus.cern.ch`) provides a cluster of machines for interactive computing as well as access to the HTCondor batch system for job submission. Provided you have a valid CERN computing account, you can access LXPLUS following these instructions:
1. Visit the list of services at the [CERN Resources Portal](https://resources.web.cern.ch/resources/Manage/ListServices.aspx), and search for boxes: LXPLUS and Linux, AFS Workspaces, EOS/CERNBox.
2. Subscribe to LXPLUS and Linux
3. Subscribe and setup your AFS Workspaces: you can have up to 10GB in `/afs/cern.ch/user/<initial>/<username>` and up to 100GB in `/afs/cern.ch/work/<initial>/<username>`. You can set these limits from the Settings in the "AFS Workspace". 
4. Subscribe to EOS/CERNBox and login to cernbox: [https://cernbox.cern.ch/](https://cernbox.cern.ch/). This will allow you access to `/eos/user/<initial>/<username>` with up to 1TB of space.

Users are recommended to setup code in their AFS Workspace areas and use their EOS/CERNBox for long term data storage.
A simple script is provided to setup the relevant software dependencies in the LXPLUS environment.
```
source lxplus_setup.sh
```

## To compile the code
* Create a new directory to contain the executables (assume the path is `/path/to/build`)
* Assume the path to the source code is `/path/to/source`
* To compile, you need to go to the build directory `cd /path/to/build`
* And then `cmake -S /path/to/source -B /path/to/build`
* Finally `make`

The minimal software requirements are:
* Geant4 v4_10_6_p01c
* ROOT v6_22_06a
* HEP_HPC v0_14_01
* HDF5 v1_10_0+

These are automatially satisfied once the `lxplus_setup.sh` script is sourced.
There is no longer an explicit GENIE dependency. However, the input GENIE `ghep` files need to be converted in the `gst` format (plain ROOT tree). The conversion can be perfomed with the native GENIE utility `gntpc`.

## Run the simulation
Once the code has been compiled, the simulation can be run by passing a macro file to the `FLArE` executable:
```
./FLArE /path/to/macro.mac
```
Several examples of macros are available in the `macros/fortvne_studies` directory.
The detector geometries can be easily imported by including one of the macros in `macros\geometry_options`.
If no macro is passed as argument, the default is `macros\vis.mac` which simply displays the current geometry.

## Macro commands (mostly for FPF studies)
### Geometry
|Command |Description | Default |
|:--|:--|:--|
|/det/saveGdml          | option for saving detector geometry in a GDML file, run before `/run/initialize`     |`false`|
|/det/checkOverlap      | check overlap of volumns during detector construction, run before `/run/initialize`  |`false`|
|/det/addFLArE          | option for adding the FLArE detector, run before `/run/initialize`                   |`true`|
|/det/addFLArEPos       | position of the FLArE detector, run before `/run/initialize`                         |`0 0 4300 mm`|
|/det/material          | option for detector material, choose `LAr` or `LKr`, run before `/run/initialize`    |`LAr`|
|/det/module            | option for tpc module option, choose `single` or `3x7`, run before `/run/initialize` |`single`|
|/det/field             | option for setting the magnetic field value in FLArE HadCather and Muon Finder       |`1 T`|
|/det/addFORMOSA        | option for adding the FORMOSA detector, run before `/run/initialize`                 |`true`|
|/det/addFORMOSAPos     | position of the FORMOSA detector, run before `/run/initialize`                       |`0 0 13870 mm`|
|/det/addFASERnu2       | option for adding the FASERnu2 detector, run before `/run/initialize`                |`true`|
|/det/addFASERnu2Pos    | position of the FASERnu2 detector, run before `/run/initialize`                      |`0 0 22023 mm`|
|/det/addFASER2         | option for adding the FASER2 detector, run before `/run/initialize`                  |`true`|
|/det/addFASER2Pos      | position of the FASER2 detector, run before `/run/initialize`                        |`0 0 42636 mm`|
|/det/magnetGeom        | option for FASER2 magnet geometry, choose `SAMURAI` or `CrystalPulling`              |`SAMURAI`|
|/det/magnetField       | option for setting the FASER2 magnetic field value                                   |`1 T`|
|/det/magnetWinX        | option for SAMURAI magnet window size along X axis                                   |`3.0 m`|
|/det/magnetWinY        | option for SAMURAI magnet window size along Y axis                                   |`1.0 m`|
|/det/magnetWinZ        | option for SAMURAI magnet window size along Z size                                   |`4.0 m`|
|/det/yokeThickX        | option for SAMURAI yoke thickness along X axis                                       |`1.5 m`|
|/det/yokeThickY        | option for SAMURAI yoke thickness along Y axis                                       |`2.0 m`|
|/det/magnetNumber      | option for number of CrystalPulling magnets                                          |`3`|
|/det/magnetInnerR      | option for CrystalPulling magnet inner radius                                        |`0.8 m`|
|/det/magnetOuterR      | option for CrystalPulling magnet outer radius                                        |`1.2 m`|
|/det/magnetLengthZ     | option for CrystalPulling magnet size along Z axis                                   |`1.25 m`|
|/det/magnetGap         | option for gap length (along Z) between CrystalPullin magnets                        |`0.5 m`|
|/det/trackingNumber    | option for number of FASER2 tracking stations in each assembly                       |`6`|
|/det/trackingNBarsX    | option for number of vertical scintillator bars (segmentation along X axis)          |`7`|  
|/det/trackingNBarsY    | option for number of horizontal scintillator bars (segmentation along Y axis)        |`3`|
|/det/trackingScinThick | option for scintillator bar thickness (along Z) in tracking layers                   |`1.0 cm`|
|/det/trackingGap       | option for gap length (along Z) between tracking stations, and gap to magnet         |` 0.5 m`|
### Event generators
|Command |Description |
|:--|:--|
|/genie/useGenie     | option for PrimaryGeneratorMessenger, set `true` to read neutrino interactions from GENIE|
|/genie/genieInput   | if `useGenie is true`, give which `.ghep.root` file to read GENIE events|
|/genie/genieIStart  | if `useGenie is true`, give the start position of the file to read GENIE events|
### Analysis
|Command |Description |
|:--|:--|
|/histo/fileName     | option for AnalysisManagerMessenger, set name of the file saving all analysis variables|
|/histo/saveHit      | if `true` save information for all hits, `false` in default to save space|
|/histo/save3DEvd    | if `true` save 3D spatial distribution of energy deposition, `false` in default|
|/histo/save2DEvd    | if `true` save 2D spatial distribution of energy deposition, `false` in default|
|/histo/circleFit    | if `true` run circle fitting and save information in output, `false` in default to save space|
|/histo/addDiffusion | if `toy` diffuse energy, if `single` diffuse single electron, `false` in default without diffusion|


## How to save an event display with high resolution using the DAWN Event Display
There is [this tutorial](https://conferences.fnal.gov/g4tutorial/g4cd/Documentation/Visualization/G4DAWNTutorial/G4DAWNTutorial.html) for use at the October 2003 Fermilab Geant4 Tutorial.
* Add `/vis/open DAWNFILE` to the mac file, after running a pass of simulation you'll find a ".prim" files suitable for viewing in DAWN.
* Run `~/dune_data/app/dawn_3_91a/dawn -d filename.prim`, and it will generate a high resolution picture with the format of EPS.
