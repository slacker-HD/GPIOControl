
CC = gcc  #编译器的型号

main:main.c mainui.o GPIOact.o
	gcc main.c  GPIOact.o mainui.o -o main -lncursesw -lpanel

mainui.o:mainui.c
	gcc -c mainui.c -lncursesw -lpanel

GPIOact.o:GPIOact.c
	gcc -c GPIOact.c  -lncursesw -lpanel

clean:
	rm main
	rm *.o


