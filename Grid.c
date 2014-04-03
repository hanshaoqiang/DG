#include <stdio.h>
#include <stdlib.h>
#include "Global.h"



int ParameterFile(){

char string;//string[100];

printf("from parameter\n");

FILE *fp = fopen("data.par","r");
 
 if(fp==0){
	perror ("Failed to open the parameter file \"data.par\"");

 return 1;
 }

	fscanf(fp,"%d",&iOrder);
	fscanf(fp,"%d",&iRK);
	fscanf(fp,"%d",&iElem);
	fscanf(fp,"%f",&iLength);
	fscanf(fp,"%f",&iStart);
	fscanf(fp,"%f",&iFinish);
	fscanf(fp,"%d",&iTest);
	fscanf(fp,"%f",&iTime);
	fscanf(fp,"%d\n",&iFlowNum);
	fclose(fp);

	printf("%d\n",iOrder);
	printf("%d\n",iRK);

iEl_Size = (iFinish - iStart)/IELEM; // ELEMENT SIZE 	

// number of nodes

	iNode = iElem +1; // +1  # of elements +1 = number of nodes |--------|-------|
	iNode = iNode +2; // add fictious nodes +2  		
iElem = iNode -1; // 2 nodes = 1 element =>  -1 accounts for the fictious element

printf ("%d %d \n", iNode, IELEM);

// number of conserved variables
	
	switch(iFlowNum){
	
	case 1:
	iConNum = 1;
	break;
		
	case 2:
	iConNum = 3;
	break;
	


}


ICFL = 0.2;

return 0;
} // end of parameter file






/*
ALLOCATE THE MEMOREY FOR THE ARRAY
*/


  int AllocateMem(){
int i,j,k;

 //float *rNodePoints;


	rNodePoints = malloc(iNode*sizeof(float));

  		if(rNodePoints ==0){
  		printf("Error Allocating Memory for node array");
  		return 1; 
  		}


	
	rXg = malloc(6*sizeof(int));
	rWg = malloc(6*sizeof(int));


		if(rXg ==0 || rWg ==0 ){
  		printf("Error Allocating Memory for gaussian quadrature");
  		return 1; 
  		}
	

	rRKAlpha =  malloc(IRK*sizeof(float));
	rRKBeta =  malloc(IRK*sizeof(float));
	rRKGamma =  malloc(IRK*sizeof(float));
	rRHS =  malloc(IFLOWNUM*sizeof(float));


sol = (double***)malloc(IELEM * sizeof(double **)); 
rRKInt = (double***)malloc(IELEM * sizeof(double **)); 

 	for(i=0;i<IELEM;i++) {
	
	sol[i] = (double**)malloc(IORDER * sizeof(double*));
	rRKInt[i] = (double**)malloc(IORDER * sizeof(double*));
          	for(j=0;j<IORDER;j++){                 
			 
	 	sol[i][j] = (double*)malloc(IFLOWNUM*sizeof(double));    
	 	rRKInt[i][j] = (double*)malloc(IFLOWNUM*sizeof(double)); 
		} 
	} 	



K1 = (double***)malloc(IELEM * sizeof(double **)); 
K2 = (double***)malloc(IELEM * sizeof(double **)); 
K3 = (double***)malloc(IELEM * sizeof(double **)); 
 	for(i=0;i<IELEM;i++) {
	
	K1[i] = (double**)malloc(IORDER * sizeof(double*));
	K2[i] = (double**)malloc(IORDER * sizeof(double*));
	K3[i] = (double**)malloc(IORDER * sizeof(double*));
          	for(j=0;j<IORDER;j++){                 
			 
	 	K1[i][j] = (double*)malloc(IFLOWNUM*sizeof(double));    
	 	K2[i][j] = (double*)malloc(IFLOWNUM*sizeof(double));
		K3[i][j] = (double*)malloc(IFLOWNUM*sizeof(double)); 	 
		} 
	} 




rVolumeFlux = (double***)malloc((IELEM-1) * sizeof(double **)); 
 	for(i=0;i<IELEM-1;i++) {

	rVolumeFlux[i] = (double**)malloc(IORDER * sizeof(double*));
		for(j=0;j<IORDER;j++){                 
			 
	 	rVolumeFlux[i][j] = (double*)malloc(IFLOWNUM*sizeof(double));    
		} 
	} 	

	rFaceFlux = (double**)malloc((iNode-2) *sizeof(double*));

	for(i=0;i<(iNode-2);i++){

	rFaceFlux[i] = (double*)malloc(IFLOWNUM *sizeof(double));

}

   



	return 0;
  }


int GridStuff(){
	
	int i;
	float rGridSize,rGridAdd; 

	rGridSize = ILENGTH/IELEM;
	
	rGridAdd =ISTART;
	
	rNodePoints[0] = ISTART;
	for(i=0; i<IELEM; i++){
	
	rGridAdd = rGridAdd + rGridSize;
	
	rNodePoints[i+1] = rGridAdd;
		
		}
	
	
	//printf("%f\n %f\n",iEl_Size, rGridSize);	
	return 0;

	}


