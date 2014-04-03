#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Global.h"
#include "par.h"


	int Godunov(){

	int i,p;
	float UL,UR;
	float rFluxL, rFluxR, test, test2;



		for(i=1;i<(INODE-1);i++){

			UL=0; UR=0;
			for(p=0;p<IORDER;p++){
	   		UL=UL + rRKInt[i-1][p][0]*Basis(p,1.0);
	   		UR=UR + rRKInt[i][p][0]*Basis(p,-1.0);
			}

		 
		
	  	rFluxL=UL;
	  	rFluxR=UR;	

		if(WaveSpeed >0){	
		rFaceFlux[i-1][0] = rFluxL;
		}

		else{
		rFaceFlux[i][0] = rFluxR;
		}
		
//if(i==6)	printf("flux %f \n", rFluxL);
		}

	}


	int VolumeFlux(){
	int i,p,j,recon;
	float rUCurrent, rFluxCurrent;
	GaussPoints();	 // gaussian points	
	for(i=0; i<(IELEM -1); i++){
		
		for(p=0; p<IORDER; p++){		
 		
		rVolumeFlux[i][p][0] = 0.0;
			for(j=0; j<6; j++){		

				rUCurrent =0.0;		

				for(recon =0; recon<IORDER; recon++){

				rUCurrent = rUCurrent + rRKInt[i][recon][0]*Basis(recon,rXg[j])	;

				}
			
				
	 		 rVolumeFlux[i][p][0] = rVolumeFlux[i][p][0] + rUCurrent*rWg[j]*Basis_X(p,rXg[j]);
		
							
			} //quad
		//if(i==0)	printf("vol %d %f \n", p, rVolumeFlux[i][p][0]);
		} // order

	} // ielem


} // end of function



 	int FluxDriver(){

	switch(IFLOWNUM){
	
	case 1: // godunov flux
	Godunov();
	break;
		
	default:
	printf("wrong flux");
	break;
	}
		
} //
	







	


 
