EnsurePythonVersion(2,7)

import os
import subprocess

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

AddOption('--update',
    dest='update',
    action='store_true',
    default=False,
    help='updates all submodules'
)


##
## other setup
##

def needs_update(subs):
    for mod in submodules:
        if GetOption('update') or not len([f for f in os.listdir(mod) if os.path.isfile(os.path.join(mod, f))]):
            return True
    return False


# initialize submodules
get_subs_cmd = [
    ['git', 'config', '--file', os.path.join(Dir('#').abspath, '.gitmodules'), '--name-only', '--get-regexp', 'path'],
    ['sed', "s/^submodule\.//"],
    ['sed', "s/\.path$//"],
]
get_subs = subprocess.Popen(get_subs_cmd[0], stdout=subprocess.PIPE)
filter_sub = subprocess.Popen(get_subs_cmd[1], stdin=get_subs.stdout, stdout=subprocess.PIPE)
get_subs.wait()
filter_sub.wait()
submodules = filter(None, subprocess.check_output(get_subs_cmd[2], stdin=filter_sub.stdout).split('\n'))
if GetOption('update') or needs_update(submodules):
    print "initializing modules..."
    subprocess.check_call(['git', 'submodule', 'init'])
    print "updating modules..."
    subprocess.check_call(['git', 'submodule', 'update', '--remote'])


# init the 'global' base environment (more added in the SConscript)
env = Environment()
SConscript('SConscript',  duplicate=False)
