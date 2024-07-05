CC=clang
CFLAGS= -c -g -Wall -O2

PURECAPFLAGS= -target aarch64-unknown-freebsd -march=morello -mabi=purecap -Xclang -morello-vararg=new

all: libcheri_sdrad.so


libcheri_sdrad.so: cheri_sdrad.o cheri_domain_setup.o cheri_sdrad_signal.o cheri_sdrad_api.o tlsf.o cheri_sdrad_heap_mng.o
	$(CC) -g -O2 -shared $(PURECAPFLAGS) -o libcheri_sdrad.so cheri_sdrad.o cheri_sdrad_signal.o cheri_sdrad_api.o cheri_domain_setup.o tlsf.o cheri_sdrad_heap_mng.o

cheri_sdrad_api.o: cheri_sdrad_api.c cheri_sdrad_api.h
	$(CC) $(CFLAGS) -fPIC $(PURECAPFLAGS) cheri_sdrad_api.c -o cheri_sdrad_api.o

cheri_domain_setup.o: cheri_domain_setup.S
	$(CC) $(CFLAGS) -fPIC $(PURECAPFLAGS) cheri_domain_setup.S -o cheri_domain_setup.o

cheri_sdrad_signal.o: cheri_sdrad_signal.c cheri_sdrad_signal.h
	$(CC) $(CFLAGS) -fPIC $(PURECAPFLAGS) cheri_sdrad_signal.c -o cheri_sdrad_signal.o

cheri_sdrad_heap_mng.o: cheri_sdrad_heap_mng.c cheri_sdrad_heap_mng.h
	$(CC) $(CFLAGS) -fPIC $(PURECAPFLAGS) cheri_sdrad_heap_mng.c -o cheri_sdrad_heap_mng.o

tlsf.o: tlsf.c tlsf.h
	$(CC) $(CFLAGS) -fPIC $(PURECAPFLAGS) tlsf.c -o tlsf.o

cheri_sdrad.o: cheri_sdrad.c cheri_sdrad.h
	$(CC) $(CFLAGS) -fPIC $(PURECAPFLAGS) cheri_sdrad.c -o cheri_sdrad.o

clean:
	rm -f *.o *.core *.so