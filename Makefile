OBJ = Lab2.o optlib.o
CFLAGS = -Wall -std=c89 -pedantic
BINARY = lab4
all: $(BINARY)

$(BINARY): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(BINARY)

%.o : %.c
	gcc $(CFLAGS) -c $<

clean:
	rm $(BINARY) $(OBJ)
