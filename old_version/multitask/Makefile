CC = riscv64-unknown-elf-gcc
CFLAGS = -g -nostdlib -fno-builtin -mcmodel=medany -march=rv64ima -mabi=lp64

QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 4 -machine virt -bios none

OBJDUMP = riscv64-unknown-elf-objdump

all: os.elf

os.elf: start.s sys.s lib.c os.c task.c user.c
	$(CC) $(CFLAGS) -T os.ld -o os.elf $^


qemu: $(TARGET)
	@qemu-system-riscv64 -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit qemu"
	$(QEMU) $(QFLAGS) -kernel os.elf

clean:
	rm -f *elf
