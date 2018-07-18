ASCII_TILING_C_FLAGS=-O2 -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winline -Wlong-long -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wno-import -Wpointer-arith -Wredundant-decls -Wshadow -Wstrict-prototypes -Wwrite-strings

ascii_tiling: ascii_tiling.o
	gcc -o ascii_tiling ascii_tiling.o

ascii_tiling.o: ascii_tiling.c ascii_tiling.make
	gcc -c ${ASCII_TILING_C_FLAGS} -o ascii_tiling.o ascii_tiling.c

clean:
	rm -f ascii_tiling ascii_tiling.o
