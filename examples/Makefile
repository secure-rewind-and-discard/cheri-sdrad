CC=clang
CFLAGS= -c -g -Wall

PURECAPFLAGS= -target aarch64-unknown-freebsd -march=morello -mabi=purecap -Xclang -morello-vararg=new
PURECAPSHAREDLIBFLAGS= -L../src -lcheri_sdrad

all: cheri_sdrad_alloc cheri_sdrad_overflow


cheri_sdrad_alloc: cheri_sdrad_alloc.o
	$(CC) $(PURECAPSHAREDLIBFLAGS) $(PURECAPFLAGS) cheri_sdrad_alloc.o -o cheri_sdrad_alloc

cheri_sdrad_alloc.o: cheri_sdrad_alloc.c
	$(CC) $(CFLAGS) $(PURECAPFLAGS) cheri_sdrad_alloc.c -o cheri_sdrad_alloc.o

cheri_sdrad_overflow: cheri_sdrad_overflow.o
	$(CC) $(PURECAPSHAREDLIBFLAGS) $(PURECAPFLAGS) cheri_sdrad_overflow.c -o cheri_sdrad_overflow

cheri_sdrad_overflow.o: cheri_sdrad_overflow.c
	$(CC) $(CFLAGS) $(PURECAPFLAGS) cheri_sdrad_overflow.c -o cheri_sdrad_overflow.o

clean:
	rm -f *.o cheri_sdrad_overflow cheri_sdrad_alloc