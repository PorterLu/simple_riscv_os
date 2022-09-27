CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -march=rv64im -mabi=lp64 -mcmodel=medany -g -Wall

QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = ${CROSS_COMPILE}gdb
CC = ${CROSS_COMPILE}gcc
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump

NPC = ${NEMU_HOME}/../myCPU/obj_dir/Vysyx_22041812_myCPU
NPC_FLAGS = -l log.txt -s ${NEMU_HOME}/nemu/build/riscv64-nemu-interpreter-so
