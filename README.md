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


Dependencies
============

## pip

Obviously, `pip`.

Available under all package managers.

1. PySerial
    * (Recommended) most package managers also have a `python-serial`
        * install the package with your distribution's package manager
            * Ubuntu: `sudo apt-get install -y python-serial`
        * let pip upgrade it for us like so:
            * `sudo pip install pyserial --upgrade`
    * Otherwise
        * `sudo pip install pyserial`


## Arduino

This project uses the native Arduino compilers, libraries, source code, and link script.

Full compatibility is to be expected with the IDE and other Arduino-compatible systems.

__*HOWEVER*__, to support the `Arduino Due` you will have to manually install the Arduino IDE and have a version of
`v1.6.8` or greater *and* manually install the `Due` support package from within the IDE.


Arduino `scons` flags:

* `--arduino-path`
    * The root path of the *Due Package*.
* `--arduino-version`
    * Version of the Arduino IDE installed.
* `--arduino-gcc-version`
    * Version of the gcc version installed with the Arduino IDE.
* `--variant`
    * Arduino variant name as seen in `boards.txt` (installed by IDE)
* `--mcu`
    * Change the `mcpu` flag to the compiler and linker


Though these should default nicely, you can see it is somewhat fragile.

The defaults are easily changed, and should be bumped regularly as official releases change.


## Build System

#### Scons

This is the main driver of the build system.

Cross-platform, python-based, and good at incremental builds.

Available under any good package manager.

Ubuntu: `sudo apt-get install -y scons`



Arduino Due
===========

```
    arduino_due_x_dbg.name=Arduino Due (Programming Port)
    arduino_due_x_dbg.vid.0=0x2341
    arduino_due_x_dbg.pid.0=0x003d
    arduino_due_x_dbg.vid.1=0x2A03
    arduino_due_x_dbg.pid.1=0x003d
    arduino_due_x_dbg.upload.tool=bossac
    arduino_due_x_dbg.upload.protocol=sam-ba
    arduino_due_x_dbg.upload.maximum_size=524288
    arduino_due_x_dbg.upload.use_1200bps_touch=true
    arduino_due_x_dbg.upload.wait_for_upload_port=false
    arduino_due_x_dbg.upload.native_usb=false
    arduino_due_x_dbg.build.mcu=cortex-m3
    arduino_due_x_dbg.build.f_cpu=84000000L
    arduino_due_x_dbg.build.usb_manufacturer="Arduino LLC"
    arduino_due_x_dbg.build.usb_product="Arduino Due"
    arduino_due_x_dbg.build.board=SAM_DUE
    arduino_due_x_dbg.build.core=arduino
    arduino_due_x_dbg.build.extra_flags=-D__SAM3X8E__ -mthumb {build.usb_flags}
    arduino_due_x_dbg.build.ldscript=linker_scripts/gcc/flash.ld
    arduino_due_x_dbg.build.variant=arduino_due_x
    arduino_due_x_dbg.build.variant_system_lib=libsam_sam3x8e_gcc_rel.a
    arduino_due_x_dbg.build.vid=0x2341
    arduino_due_x_dbg.build.pid=0x003e
    
    arduino_due_x.name=Arduino Due (Native USB Port)
    arduino_due_x.vid.0=0x2341
    arduino_due_x.pid.0=0x003e
    arduino_due_x.vid.1=0x2A03
    arduino_due_x.pid.1=0x003e
    arduino_due_x.upload.tool=bossac
    arduino_due_x.upload.protocol=sam-ba
    arduino_due_x.upload.maximum_size=524288
    arduino_due_x.upload.use_1200bps_touch=true
    arduino_due_x.upload.wait_for_upload_port=true
    arduino_due_x.upload.native_usb=true
    arduino_due_x.build.mcu=cortex-m3
    arduino_due_x.build.f_cpu=84000000L
    arduino_due_x.build.usb_manufacturer="Arduino LLC"
    arduino_due_x.build.usb_product="Arduino Due"
    arduino_due_x.build.board=SAM_DUE
    arduino_due_x.build.core=arduino
    arduino_due_x.build.extra_flags=-D__SAM3X8E__ -mthumb {build.usb_flags}
    arduino_due_x.build.ldscript=linker_scripts/gcc/flash.ld
    arduino_due_x.build.variant=arduino_due_x
    arduino_due_x.build.variant_system_lib=libsam_sam3x8e_gcc_rel.a
    arduino_due_x.build.vid=0x2341
    arduino_due_x.build.pid=0x003e
```



