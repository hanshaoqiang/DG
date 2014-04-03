#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "par.h"
#include "Global.h"



 int main() {
	float gg;
	printf("******************************************\n");
	printf("DG program(hyperbolic conservation law)\n");
	printf("*****************************************\n\n");


	printf("reading in parameter file\n");
	// reading in the parameter file

	

	ParameterFile(); // open the parameter file
	printf("Allocating memory for global arrays\n");	
	AllocateMem();	 // allocate memory for global arrays
	GridStuff();	
	GaussPoints();	 // gaussian points			
	RungeKutta();
	


}









