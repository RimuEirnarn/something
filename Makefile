all: run

run:
	gcc -c main.c -o main.exe
	./main.exe
	rm main