OBJ = Lab2.o optlib.o
CFLAGS = -Wall -std=c89 -pedantic
BINARY = lab2
all: bin

bin: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(BINARY)

%.o : %.c
	gcc $(CFLAGS) -c $<

clean:
	rm bin $(OBJ)
