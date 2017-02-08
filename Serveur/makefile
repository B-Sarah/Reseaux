.PHONY : all clean

serveur : serveur.o clientHandler.o
	gcc -o serveur serveur.o clientHandler.o -lpthread
serveur.o : serveur.c serveur.h
clientHandler.o: clientHandler.c clientHandler.h
clean: 
	@rm *.o
