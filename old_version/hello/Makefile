CC = riscv64-unknown-elf-gcc
CFLAGS = -nostdlib -fno-builtin -mcmodel=medany -march=rv64ima -mabi=lp64

QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 4 -machine virt -bios none

OBJDUMP = riscv64-unknown-elf-objdump

all: os.elf

os.elf: start.S os.c
	$(CC) $(CFLAGS) -T os.ld -o os.elf $^


qemu: $(TARGET)
	@qemu-system-riscv64 -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit qemu"
	$(QEMU) $(QFLAGS) -kernel os.elf

clean:
	rm -f *elf
