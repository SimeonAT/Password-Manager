FILENAME = infinite-windows

all:
	make create

create: $(FILENAME).c
	gcc -o $(FILENAME) $(FILENAME).c `pkg-config --cflags --libs gtk4`

clean:
	rm -f $(FILENAME)
