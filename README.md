vesUVius
========

First Steps
===========

Before you can build or use this repository, we need to initialize the submodules we use.

From this directory, run the following:

```
$ git submodule init
$ git submodule update
```

Alternatively,

```
$ init_or_update.sh
```


Dependencies
============

For Debian-based distros (Ubuntu for instance): `$ utils/install_deps/deb.sh`



## pyserial

Available under most package managers, or via `pip`.

__*(Recommended):*___ install the package with your distribution's package manager
  * Ubuntu: `sudo apt-get install -y python-serial`


Otherwise: `sudo pip install pyserial`


## Arduino

This project uses the native Arduino compilers, libraries, source code, and link script.

Full compatibility is to be expected with the IDE and other Arduino-compatible systems.

__*HOWEVER*__, to maintain CI, command line compatability, and ease of use the libraries are extracted and mirrored
in a submodule (owned by this organization). This removes the need for installing the Arduino IDE, Java, or manually
installing the boards via GUI.


## gcc-arm-none-eabi

A compiler for the ARM platform is required.
  * Ubuntu: `sudo apt-get install -y gcc-arm-none-eabi`





## Build System

### Scons

This is the main driver of the build system.

Cross-platform, python-based, and good at incremental builds.

Available under any good package manager.

Ubuntu: `sudo apt-get install -y scons`


### Building


To see all compilation options: `$ scons --help`.

To compile the controller (and the `arduino-core` libraries) simply run `$ scons`.


#### Flashing

Flashing the program to the arduino can be done using `pyserial` via:

```
$ scons --upload
```
