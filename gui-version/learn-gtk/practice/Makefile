FILENAME = hello-there

all:
	make create

create: $(FILENAME).c
	gcc -o $(FILENAME) $(FILENAME).c `pkg-config --cflags --libs gtk4`

clean:
	rm -f $(FILENAME)

valgrind:
	G_DEBUG=resident-modules valgrind --tool=memcheck --leak-check=full --leak-resolution=high --num-callers=20 --log-file=vgdump ./infinite-windows
