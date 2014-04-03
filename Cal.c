#include <stdio.h>
#include <math.h>
#include "Global.h"

/*
Basis functions
Derivatives of Basis functions
Norms of Basis functions
Quadrature points
coefficents of RK
initial conditions
*/
int AllocateMem();

//***************************************
// Basis functions
//****************************************


	float Basis(int order,float x){
		float answer;
	
		switch(order){
			case 0:
			answer = 1;
			break;
			
			case 1:
			answer = x;
			break;
			
			case 2:
			answer = 0.5*(3*pow(x,2) - 1);
			break;		
			
			case 3:
			answer = 0.5*(5*pow(x,3) - 3*x);
			break;	
	
			case 4:
			answer = (1./8.)*(35*pow(x,4) - 30*pow(x,2) + 3);
			break;	

			case 5:
			answer = (1./8.)*(63*pow(x,5) - 70*pow(x,3) + 15*x);
			break;
			
		}

		return(answer);	

	}

//***************************************
// derivative of Basis functions
//****************************************
	
	float Basis_X(int order, float x){
		float answer;
	
		switch(order){
			case 0:
			answer = 0;
			break;
			
			case 1:
			answer = 1;
			break;
			
			case 2:
			answer = 3*x;
			break;		
			
			case 3:
			answer = 0.5*(15*pow(x,2) - 3);
			break;	
	
			case 4:
			answer = (1./8.)*(140*pow(x,3) - 60*pow(x,1));
			break;	

			case 5:
			answer = (1./8.)*(315*pow(x,4) - 210*pow(x,2) + 15);
			break;
			
		}

		return(answer);	

	}



	float GaussPoints(){


   rXg[0] =   0.23861918;
   rXg[1] =   0.66120939;
   rXg[2] =   0.93246951;

   rXg[3] = - 0.23861918;
   rXg[4] = - 0.66120939;
   rXg[5] = - 0.93246951;
   
   rWg[0] = 0.46791393;
   rWg[1] = 0.36076157;
   rWg[2] = 0.17132449;
   rWg[3] = 0.46791393;
   rWg[4] = 0.36076157;
   rWg[5] = 0.17132449;
}



float Norms(int iorder){
float answer;

answer  = 2.0/(2.0*iorder + 1);

return (answer);
}


float RKINT(){

switch(IRK){

	case 1:
	
	rRKAlpha[0]=1.0;
	
	rRKBeta[0]= 0.0;
	
	rRKGamma[0]= 1.0;
	
/*
		rRKAlpha(1)=1.D0
		rRKAlpha(2)=0.5D0
		rRKBeta(1)= 0.D0
		rRKBeta(2)= 0.5D0
		rRKGamma(1)= 1.0D0
		rRKGamma(2)= 0.5D0
*/
case 2:	
	rRKAlpha[0]=1.0;
	rRKAlpha[1]=0.5;
	rRKBeta[0]= 0.0;
	rRKBeta[1]= 0.5;
	rRKGamma[0]= 1.0;
	rRKGamma[1]= 0.5; //1.0
 break;	


 case 3:

		rRKAlpha[0]=1.0;
		rRKAlpha[1]=0.75;
		rRKAlpha[2]=1.0/3.0; 

		rRKBeta[0]= 0.0;
		rRKBeta[1]= 0.25;
		rRKBeta[2]= 2.0/3.0;

		rRKGamma[0]= 1.0;
		rRKGamma[1]= 0.25;
		rRKGamma[2]= 2.0/3.0;


 break;

}

}
