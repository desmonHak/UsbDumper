CC = gcc
SFLAGS = -v -Wall -Wextra -Werror -O2 -pipe -ggdb -S -masm=intel
CFLAGS = -v -Wall -Wextra -Werror -O2 -pipe -ggdb
ARCH_x86=-m32
ARCH_x86=-m64
OBJECTS = main.o is.o listin.o cp.o \
		  concat_name.o dirtoname.o \
		  mkdir.o detect.o
