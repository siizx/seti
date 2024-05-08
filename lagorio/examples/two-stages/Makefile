all: 1st-stage 2nd-stage

1st-stage: 1st-stage.o
	$(CC) $(CFLAGS) -o 1st-stage 1st-stage.c
	sudo chown root.root 1st-stage
	sudo chmod ogu+rx 1st-stage
	sudo chmod +s 1st-stage


2nd-stage: 2nd-stage.o

clean:
	sudo rm -f 1st-stage 1st-stage.o 2nd-stage 2nd-stage.o

