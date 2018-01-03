all: main

LIBPI=fakesd.c ../../src/fat.c ../../src/fs.c

main: $(LIBPI) main.c
	$(CC) -I../../include $^ -DUNIT_TEST -o main

clean: $(LIBPI) main.c
	rm main
