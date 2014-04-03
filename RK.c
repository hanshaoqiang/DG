#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Global.h"
#include "math.h"
#include "par.h"







int CalculateRHS(){

int i, p;

		FluxDriver(); // RIEMANN CALL
		VolumeFlux(); // volume flux
	for(i=1; i<IELEM-1; i++){ // khi :: 22/07/2012

			for(p=0; p<IORDER; p++ ){	


	     		rRKInt[i][p][0]  = 0. ; 
			
			rRKInt[i][p][0] = rRKInt[i][p][0] - (rFaceFlux[i][0]*Basis(p,1.0)-  rFaceFlux[i-1][0]*Basis(p,-1.0));
 			
			
			rRKInt[i][p][0] =  rRKInt[i][p][0] + rVolumeFlux[i][p][0];

			   		
			rRKInt[i][p][0] = rRKInt[i][p][0]/Norms(p)*(2.0/iEl_Size);    		
			
			
//if(rRKInt[i][p][0] > 1000.0){printf("%f \n", rRKInt[i][p][0]);
//exit(EXIT_FAILURE);
//}
			}
 		
		}

		for(p=0; p<IORDER; p++ ){
			
			rRKInt[IELEM-1][p][0]=rRKInt[1][p][0]; // checked khi
			rRKInt[0][p][0]=rRKInt[IELEM-2][p][0]; // checked khi	

			}

}

int RungeKutta(){
double tol,rCurrent;
double rDT,midpoint;

int i,p,k,r,pp,t ;

float test, S, L0;

double uat1, uathold;;

tol  = 0.00000001;
rCurrent = 0.0;

AdvecInit();

RKINT();
t=0;
rDT = 0.0;
while(rCurrent<ITIME){ 
// calculate the size of the time step
 rDT =  CFL*iEl_Size;
 rDT = MIN(ITIME - rCurrent,rDT);

 
for(i=0; i<IELEM; i++){ // khi :: 22/07/2012
for(p=0; p<IORDER; p++ ){	
rRKInt[i][p][0]=sol[i][p][0]; // copy solution to temp array for runge-kutta
}
}
	for (r=0; r<IRK; r++){ // khi :: 22/07/2012


		VolumeFlux(); // volume flux
		FluxDriver(); // RIEMANN CALL
		
		for(i=1; i<(IELEM-1); i++){ // khi :: 22/07/2012

		//if(i==6)printf("%d %f \n",t, rFaceFlux[i-1][0]);

			for(p=0; p<IORDER; p++ ){	


	     		rRHS[0]  = 0. ; 
			
			rRHS[0] =  rRHS[0] - (rFaceFlux[i][0]*Basis(p,1.0)-  rFaceFlux[i-1][0]*Basis(p,-1.0));
 			//if(i==23)printf("%d: %f \n", p, rFaceFlux[i][0]);
			
			rRHS[0] =  rRHS[0] + rVolumeFlux[i][p][0];

			//rRHS[0] =  rRHS[0]/iEl_Size;    		
			rRHS[0] =  (2.0*rRHS[0])/(Norms(p)*iEl_Size);    		
			
			rRKInt[i][p][0]= rRKAlpha[r]*sol[i][p][0]+rRKBeta[r]*rRKInt[i][p][0]+  rDT*rRKGamma[r]*rRHS[0];	

		
		//exit(EXIT_FAILURE);	
			}
 		
		}


   	
			for(p=0; p<IORDER; p++ ){
			
			rRKInt[IELEM-1][p][0]=rRKInt[1][p][0]; // checked khi
			rRKInt[0][p][0]=rRKInt[IELEM-2][p][0]; // checked khi	

			}




	}
//printf("%d %f \n",i, rRKInt[5][0][0]);
//if(t==0)exit(EXIT_FAILURE);
for(i=0; i<IELEM; i++){ // khi :: 22/07/2012
for(p=0; p<IORDER; p++ ){	
sol[i][p][0]=rRKInt[i][p][0]; // copy solution to temp array for runge-kutta
}
}	

printf("%d: %f \n",t, rCurrent);

rCurrent = rCurrent + rDT;

t = t+1;

}


FILE *kpp = fopen("Final.dat","w");
midpoint = IEL_SIZE/2.0;
	//L0= 0;
	//S=0.;	
	for(i=1; i<(INODE-1); i++){	
	
	fprintf(kpp,"%f %f %f \n",midpoint,rRKInt[i][0][0] , InitCond(midpoint - ITIME));
	midpoint  = midpoint + IEL_SIZE;  
	
	S = ABS(rRKInt[i][0][0] - InitCond(midpoint - ITIME));
	L0 = MAX(L0,S);
	//printf("%f \n",L0);
	}

fclose(kpp);


}


int RKTEST(){

int r;
float t,k1, k2, deltaT;
float y0, update,rhs;
t=1; // starting time
y0 =1; // initial conditions
deltaT = 0.025; //time step
	
	while(t<1.2){
	update = y0;	
	//printf("%f %f \n",t, y0);	
	k1 = tan(y0) + 1;	

	k2 = tan(y0+0.66666*deltaT*k1) + 1;
	

	update = y0 + deltaT*(0.25*k1 + 0.75*k2);

	
	y0= update;
	
	
	t = t +deltaT;
	
	
	}

	
}


int RK2(){
double tol,rCurrent;
double rDT,midpoint;

int i,p,k,r,pp,t ;

float test, S, L0;

double uat1, uathold;;

tol  = 0.00000001;
rCurrent = 0.0;

AdvecInit();


t=0;
rDT = 0.0;
while(rCurrent<ITIME){ 
// calculate the size of the time step
 rDT =  CFL*iEl_Size;
 rDT = MIN(ITIME - rCurrent,rDT);

 

//rRKInt=sol; // copy solution to temp array for runge-kutta

	for(i=1; i<IELEM-1; i++){ 
		
		for(p=0; p<IORDER; p++){
	rRKInt[i][p][0] = sol[i][p][0];	
	
		}
	}


// k1		

		CalculateRHS(); // this is k1
	
	for(i=1; i<IELEM-1; i++){ 
		
		for(p=0; p<IORDER; p++){
	K1[i][p][0]  = rRKInt[i][p][0];
	rRKInt[i][p][0] = sol[i][p][0] + (2.0/3.0)*rDT*K1[i][p][0] ;
		K2[i][p][0] = rRKInt[i][p][0]; 
		}
	}
   	

		CalculateRHS(); // this is k1
		

	for(i=1; i<IELEM-1; i++){ 
		
		for(p=0; p<IORDER; p++){
	
	rRKInt[i][p][0] =  sol[i][p][0] + rDT*(0.25*K1[i][p][0] + 0.75*K2[i][p][0]); 
		
	printf("%f \n", rRKInt[i][p][0]);		
	sol[i][p][0] = rRKInt[i][p][0]; // copy solution back			
		}
	}
//update = y0 + deltaT*(0.25*k1 + 0.75*k2);


// apply BC
		


	
//printf("%d %f \n",i, rRKInt[5][0][0]);
//if(t==0)exit(EXIT_FAILURE);
	
rCurrent = rCurrent + rDT;
t = t+1;

}


FILE *kkpp = fopen("Final.dat","w");
midpoint = IEL_SIZE/2.0;
	//L0= 0;
	//S=0.;	
	for(i=1; i<(INODE-1); i++){	
	
	fprintf(kkpp,"%f %f %f \n",midpoint,rRKInt[i][0][0] , InitCond(midpoint - ITIME));
	midpoint  = midpoint + IEL_SIZE;  
	
	S = ABS(rRKInt[i][0][0] - InitCond(midpoint - ITIME));
	L0 = MAX(L0,S);
	//printf("%f \n",L0);
	}

fclose(kkpp);


}






