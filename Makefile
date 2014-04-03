#make file

chi: Main.o Cal.o Grid.o Init.o GlobalVar.o Flux.o RK.o
	gcc -o chi Main.o Cal.o Grid.o Init.o GlobalVar.o  Flux.o RK.o -lm
Main.o: Main.c 
	gcc -c -std=c99  Main.c -lm 
Cal.o: Cal.c  
	gcc -c -std=c99 Cal.c -lm
Grid.o: Grid.c 
	gcc -c -std=c99 Grid.c -lm
Init.o: Init.c 
	gcc -c -std=c99 Init.c -lm
GlobalVar.o: GlobalVar.c 
	gcc -c -std=c99 GlobalVar.c -lm
Flux.o: Flux.c 
	gcc -c -std=c99 Flux.c -lm
RK.o: RK.c
	gcc -c -std=c99 RK.c -lm
clean:
	rm -rf *o chi	
