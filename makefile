
CC = gcc  #编译器的型号

main:main.c mainui.o
	gcc main.c  mainui.o -o main -lncursesw -lpanel

mainui.o:mainui.c
	gcc -c mainui.c  -lncursesw -lpanel

clean:
	rm main
	rm *.o


