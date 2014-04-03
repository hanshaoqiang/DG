#include <stdio.h>
#include <stdlib.h>

extern int iOrder,iRK, iNode, iElem,iTest,iFlowNum, iConNum;
extern float iLength, iStart,iFinish,iTime,iCfl;

extern float *rNodePoints , *rXg , *rWg, *rRHS;
extern float *rRKAlpha,*rRKBeta,*rRKGamma;
extern double ***sol,***rRKInt, **rFaceFlux, ***rVolumeFlux;
extern double  ***K1,  ***K2, ***K3; 
		
