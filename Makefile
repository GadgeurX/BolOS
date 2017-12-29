CC	:= i686-elf-gcc

ASM	:= nasm

RM	:= rm -f

LDFLAGS	+= -lgcc -ffreestanding -O2 -nostdlib

CFLAGS	+= -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iincludes -g

CSRCS	:= $(shell find srcs -type f -name "*.c")

INCLUDES	:= $(shell find includes -type f -name "*.h")

TEMPFILES	:= $(shell find . -type f -name "*~")

ASRCS	:= $(shell find srcs -type f -name "*.asm")

COBJS	:= $(CSRCS:.c=.o)

AOBJS	:= $(ASRCS:.asm=.o)

NAME	:= kernel.bin

all: $(NAME)

$(AOBJS):
	for src in $(ASRCS); do \
		$(ASM) -felf32 $$src; \
	done

$(NAME): $(COBJS) $(AOBJS)
	$(CC) -T linker.ld -o $(NAME) $(COBJS) $(AOBJS) $(LDFLAGS)

clean:
	$(RM) $(COBJS) $(AOBJS)

fclean: clean
	$(RM) $(NAME)

indent:
	indent $(CSRCS) $(INCLUDES) -nbad -bap -bbo -nbc -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -cp33 -cs -d0 -di1 -nfc1 -nfca -hnl -i4 -ip0 -l75 -lp -npcs -nprs -npsl -saf -sai -saw -nsc -nsob -nss -bli0
	$(RM) $(TEMPFILES)

qrun:
	qemu-system-i386 -kernel $(NAME) -S -s

brun:
	bochs.exe -f bochsrc.bxrc

iso:
	cp kernel.bin iso/boot
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o kernel.iso iso

re: fclean all

.PHONY: all re clean fclean indent iso
