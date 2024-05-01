run-echo: run-echo.c
	$(CC) $(CFLAGS) -o run-echo run-echo.c
	sudo chown root.root run-echo
	sudo chmod ogu+rx run-echo
	sudo chmod +s run-echo

clean:
	sudo rm -f run-echo
