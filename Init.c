#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Global.h"
#include "par.h"
// DRIVER FOR THE INITIAL CONDITIONS

/*



	int Driver(){
	
	switch(IFLOWNUM){
		case 1:
		AdvecInit();
		break;
	}
		
		
	
}


*/

float InitCond( double x){
	
double answer;

	
	switch(iTest){
		case 0:
		answer = 2.0;
		break;	

		case 1:
		answer = sin(2.0*PI*x);
		break;
	
		case 2:
		
		if(x<0.25 || x>0.75){			
		answer = 0;
		}
		
		else{
		answer = 1;
		}
		
		break;
	
		default:
		printf("this init doesn't exist \n");
		exit(EXIT_FAILURE);		
		break;	
	
	}

	return (answer);

}



float AdvecInit(){
int i, p, j,k;
float c, midpoint, X_Points;
double answer;



midpoint = IEL_SIZE/2.0;

for (i=1; i<IELEM; i++)	{ 
	
	for (k=0; k<IFLOWNUM; k++)  {			
	
	
		for (p=0; p<IORDER; p++)  {

			
			sol[i][p][k] = 0.0;

			for (j=0; j<6; j++) {

X_Points =  midpoint + 0.5*IEL_SIZE*rXg[j];



sol[i][p][k] = sol[i][p][k] + InitCond((double)X_Points)*Basis(p,rXg[j])*rWg[j];


			} // quad

sol[i][p][k] = sol[i][p][k]/Norms(p);
	
		}// order

	} // flow component



midpoint  = midpoint + IEL_SIZE;

}// element


FILE *fpp = fopen("Init.dat","w");
for (i=0 ; i<INODE-1; i++){

fprintf(fpp,"%d %f\n",i,sol[i][0][0] );
//i++; 
}

fclose(fpp);

}



