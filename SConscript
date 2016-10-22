import os
import re
import fnmatch
import multiprocessing

from collections import OrderedDict


##
## project options
##

PROJ_NAME = 'vesuvius'
PROJ_SRC = 'src'



##
## compiler/linker options
##

LIBPATH = [
    os.path.join(GetOption('outdir'), 'lib'),
]

# passed to the linker
LIBS = [
]

# included from the Arduino root path
ARDUINO_LIBS = [
    'Wire',
]

STRICTFLAGS=[
    '-Wabi',
    '-Wno-unused-parameter',
    '-Wall',
    '-Wextra',
    '-Werror',
]

COMMONFLAGS=[
    '-ffunction-sections',
    '-fdata-sections',
    '-nostdlib',
    '--param',
    'max-inline-insns-single=500',
    '-mthumb',
    '-mno-thumb-interwork',
    '-mfpu=vfp',
    '-msoft-float',
    '-mfix-cortex-m3-ldrd',
    '-O2',

    '-mcpu=%s' % GetOption('mcu'),
]


LINKFLAGS=[
    '-lm',
    '-lgcc',
    '-lg',
    '-lc',
    '-mthumb',
]

CPPDEFINES = {
    'printf': 'iprintf',
    'F_CPU': '84000000L',
    '__SAM3X8E__': None,
    'USB_PID': '0x003e',
    'USB_VID': '0x2341',
    'USBCON': None,
    'ARM_MATH_CM3': None,
}

defs = ['-D{}{}'.format('{}='.format(k) if v is not None else k, v if v is not None else '')  for k, v in CPPDEFINES.iteritems()]
COMMONFLAGS.extend(defs)

CFLAGS=[
    #'-fPIC',
    '-std=gnu11',
]

CPPPATH = [
    # add c++ paths here
]

CPPFLAGS = [
    '-std=gnu++11',
    '-fno-rtti',
    '-fno-exceptions',
]



##
## Define some option-gets
##

tool_prefix = GetOption('tool_prefix')


##
## Helper Functions
##

def append_flags(src, to):
    for i in src:
        if i not in to:
            to.append(i)


def get_files(env, root, ext):
    #directory of SConstruct
    rootpath = Dir('#').abspath
    srcroot = os.path.join(rootpath, root)
    if not os.path.exists(srcroot):
        raise Exception('{} does not exist'.format(srcroot))

    src = []
    for root, dirs, files in os.walk(srcroot, followlinks=True):
        for filename in fnmatch.filter(files, '*.%s'%ext):
            src.append(os.path.join(root, filename)[len(srcroot)+1:])
    return src


def get_board_info(root_path, board_name):
    boards_path = os.path.join(root_path, 'boards.txt') # TODO: check existence
    with open(boards_path, 'r') as f:
        lines = filter(lambda l: l.startswith(board_name), map(lambda l: l.strip(), f.readlines()))

        result = {'board_name': board_name}
        for entry in lines:
            longkey, value = entry.split('=')
            parts = filter(lambda e: e != board_name, longkey.split('.'))
            if len(parts) == 1:
                result[parts[0]] = value
            elif len(parts) == 2:
                section, key = parts
                if section not in result:
                    result[section] = {}
                result[section][key] = entry[entry.rfind('=')+1:]
            else:
                raise RuntimeError("could not find board: {}".format(board_name))
    return result




##
## Final pre-environment setup
##

gcc_version = GetOption('gcc_version')
libsam_dir = 'src/ext/libsam'
arduino_library_path = libsam_dir+'/arduino/libraries'

# TODO TODO TODO TODO TODO: ewww
# include paths for libsam
libduino_paths = {
    # libsam
    'sam_lib':          libsam_dir+'/system/libsam',                        # base sam header (chip.h)
    'sam_lib_hdr':      libsam_dir+'/system/libsam/include',                # generic sam headers
    'sam_root':         libsam_dir+'/system/Device/ATMEL',                  # ATMEL sam base header
    'sam_core':         libsam_dir+'/system/Device/ATMEL/Include',          # ATMEL sam core headers
    'sam3xa_core':      libsam_dir+'/system/Device/ATMEL/sam3xa/include',   # sam3xa specific headers
    'CMSIS_core':       libsam_dir+'/system/CMSIS/Include',                 # CMSIS shared headers
    'arm_cortexm4':     libsam_dir+'/system/Device/ARM/ARMCM3/Include',     # cortex-m4 shared headers

    # arduino
    'arduino_core':     libsam_dir+'/arduino',                              # arduino due specific header
    'arduino_libs':     arduino_library_path,                               # core arduino libraries
    'arduino_variant':  libsam_dir+'/variants/arduino_due_x',               # arduino due specific header
}

COMMONFLAGS.extend(['-I{}'.format(path) for _, path in libduino_paths.iteritems()])
COMMONFLAGS.extend(['-I{}'.format(os.path.join(arduino_library_path, lib, 'src')) for lib in ARDUINO_LIBS ])

# stdlib include paths (they are nonstandard on x86 so must be manually set)
stdlib_paths = {
    'base':             '/usr/lib/arm-none-eabi/include/',
    'base_cpp':         '/usr/lib/arm-none-eabi/include/c++/{}'.format(gcc_version),
    'arm7em':           '/usr/lib/arm-none-eabi/include/c++/{}/arm-none-eabi/armv7e-m'.format(gcc_version),
}
COMMONFLAGS.extend(['-I{}'.format(path) for _, path in stdlib_paths.iteritems()])


if GetOption('dbg'):
    print "WARN: debug not implemented"

##
## Add helpers to env
##

AddMethod(Environment, get_files)
AddMethod(Environment, get_board_info)

##
## Build Entry
##
SetOption('num_jobs', int(multiprocessing.cpu_count()))


# combine the flags
CFLAGS.extend(COMMONFLAGS)
CPPFLAGS.extend(COMMONFLAGS)

global_env = Environment(
    PROJ_NAME      = PROJ_NAME,

    LIBS           = LIBS,
    LIBPATH        = LIBPATH,
    CPPPATH        = CPPPATH,
    CXXFLAGS       = CPPFLAGS,
    CFLAGS         = CFLAGS,
    LINKFLAGS      = LINKFLAGS,
    STRICTFLAGS    = STRICTFLAGS,

    STDLIB_INCLUDE = GetOption('stdlib_include'),
    GCC_VERSION    = GetOption('gcc_version'),
    CHIP_FAMILY    = GetOption('chip_family'),


    CC             = '{}-gcc'.format(tool_prefix),
    CXX            = '{}-g++'.format(tool_prefix),
    LD             = '{}-ld'.format(tool_prefix),
    AR             = '{}-ar'.format(tool_prefix),
    SIZE           = '{}-size'.format(tool_prefix),
    OBJCOPY        = '{}-objcopy'.format(tool_prefix),
    OBJDUMP        = '{}-objdump'.format(tool_prefix),
    RANLIB         = '{}-ranlib'.format(tool_prefix),


    ASCOMSTR       = "[ ASM ]\t$TARGET" if not GetOption('ugly') else None,
    ASPPCOMSTR     = "[ ASM ]\t$TARGET" if not GetOption('ugly') else None,
    CCCOMSTR       = "[ CC  ]\t$TARGET" if not GetOption('ugly') else None,
    CXXCOMSTR      = "[ CPP ]\t$TARGET" if not GetOption('ugly') else None,
    LINKCOMSTR     = "[ LD  ]\t$TARGET" if not GetOption('ugly') else None,
    ARCOMSTR       = "[ AR  ]\t$TARGET" if not GetOption('ugly') else None,
    RANLIBCOMSTR   = "[ LIB ]\t$TARGET" if not GetOption('ugly') else None,


    PROGSUFFIX              = '.elf',
    TOOL_PREFIX             = tool_prefix,
    MCU                     = GetOption('mcu'),
    #ARDUINO_BOSSAC_PATH     = arduino_bossac_path,
)

# allow colored terminal
if 'TERM' in os.environ:
    global_env['ENV']['TERM'] = os.environ['TERM']

##
## Build Targets
##

builds = OrderedDict([
    #('arduino_core', 'src/arduino_core'),
    ('libarduino',   {'path':'src/ext/libsam',  'is_lib':True,  'include':True}),
    ('controller',   {'path':'src/controller',  'is_lib':True,  'include':True}),
])
Export('global_env')


build_targets = {}
Export('build_targets')
def make_target(env, name, info):
    out = os.path.join(GetOption('outdir'), os.path.basename(info['path']))
    # add the SConscript found in the source path to build targets
    build_targets[name] = SConscript(os.path.join(info['path'], "SConscript"), variant_dir=out, duplicate=False)
    # create an alias for the names target
    global_env.Alias(name, build_targets[name])

    if info['is_lib'] == True:
        env.Append(CFLAGS = '-l{}'.format(build_targets[name][0].path))
        env.Append(CXXFLAGS = '-l{}'.format(build_targets[name][0].path))

    if info['include'] == True:
        env.Append(CFLAGS = '-I{}'.format(info['path']))
        env.Append(CXXFLAGS = '-I{}'.format(info['path']))


for name, info in builds.iteritems():
    make_target(global_env, name, info)

# define dependency graph
Depends('controller', 'libarduino')

# check if we should upload to the board
if GetOption('do_upload'):
    utilpath = 'utils/upload'
    outdir = os.path.join(GetOption('outdir'), utilpath)
    sconscript = os.path.join(utilpath, "SConscript")

    global_env.Alias('upload', SConscript(sconscript, variant_dir=outdir, duplicate=False))
    Depends('upload', 'controller')


Clean('.', GetOption('outdir'))
Default('controller')
