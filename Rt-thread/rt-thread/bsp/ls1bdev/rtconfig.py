# CPU options
ARCH='mips'
CPU ='loongson_1b'

# toolchains options
CROSS_TOOL  = 'gcc'
PLATFORM    = 'gcc'
EXEC_PATH   = 'E:/Program Files/CodeSourcery/Sourcery G++ Lite/bin'
BUILD       = 'debug'

PREFIX = 'mips-sde-elf-'
CC = PREFIX + 'gcc'
AS = PREFIX + 'gcc'
AR = PREFIX + 'ar'
LINK = PREFIX + 'gcc'
TARGET_EXT = 'elf'
SIZE = PREFIX + 'size'
OBJDUMP = PREFIX + 'objdump'
OBJCPY = PREFIX + 'objcopy'
READELF = PREFIX + 'readelf'

DEVICE = ' -mips32'
CFLAGS = DEVICE + ' -EL -G0 -mno-abicalls -fno-pic -fno-builtin -fno-exceptions -ffunction-sections -fomit-frame-pointer'
AFLAGS = ' -c' + DEVICE + ' -EL -fno-pic -fno-builtin -mno-abicalls -x assembler-with-cpp -DSYSTEM_STACK=0x80003fe8'
LFLAGS = DEVICE + ' -EL -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T ls1b_ram.lds'

CPATH = ''
LPATH = ''

if BUILD == 'debug':
    CFLAGS += ' -O0 -gdwarf-2'
    AFLAGS += ' -gdwarf-2'
else:
    CFLAGS += ' -O2'

DUMP_ACTION = OBJDUMP + ' -D -S $TARGET > rtt.asm\n'
READELF_ACTION = READELF + ' -a $TARGET > rtt.map\n'
POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'
