EnsurePythonVersion(2,7)

import os

##
## build options
##

AddOption('--out',
    nargs=1,
    dest='outdir',
    action='store',
    default='bin',
    help='directory to use as the variant directory'
)
AddOption('--dbg',
    action='store_true',
    help='compile binary/libraries in debug mode (-O0, non-stripped)'
)
AddOption('--ugly',
    action='store_true',
    help='print the entire file-compilation string rather than pretty-printing'
)
AddOption('--tool-prefix',
    dest='tool_prefix',
    action='store',
    default='arm-none-eabi',
    help='prefix on all compilers/tools we will use'
)

##
## compiler options
##


AddOption('--stdlib-include',
    dest='stdlib_include',
    action='store',
    default='/usr/lib/arm-none-eabi/include/',
    help='Path to the arm-none-eabi library include path'
)

AddOption('--gcc-version',
    dest='gcc_version',
    action='store',
    default='4.9',
    help='gcc-arm version number (part of stdlib include, typically only the format X.Y)'
)

AddOption('--mcu',
    dest='mcu',
    action='store',
    default='cortex-m3',
    help='MCU on the board you are building for as seen in boards.txt'
)

AddOption('--chip-family',
    dest='chip_family',
    action='store',
    default='armv7e-m',
    help='ARM chip (core) family'
)


##
## command options
##

AddOption('--upload',
    dest='do_upload',
    action='store_true',
    default=False,
    help='upload the program to the board'
)


##
## other setup
##

# init the 'global' base environment (more added in the SConscript)
env = Environment()
SConscript('SConscript',  duplicate=False)
