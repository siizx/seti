all: runner stealer

runner: runner.o
	$(CC) $(CFLAGS) -o runner runner.c
	sudo chmod 600 a-secret
	sudo chown root.root a-secret
	sudo chown root.root runner
	sudo chmod ogu+rx runner
	sudo chmod +s runner


stealer: stealer.o

clean:
	sudo rm -f runner runner.o stealer stealer.o
	sudo chmod 666 a-secret

