#ifndef GLOBAL_H
#define GLOBAL_H

//global variables
 int iOrder,iRK, iNode, iElem,iTest, iFlowNum,iConNum;
 float iLength, iStart,iFinish,iTime, iEl_Size, iCfl;

float *rNodePoints , *rXg , *rWg, *rRHS;
float *rRKAlpha,*rRKBeta,*rRKGamma;
double ***sol, ***rRKInt, **rFaceFlux, ***rVolumeFlux;
double  ***K1,  ***K2, ***K3; 
//float

// global variables DEFINED
#define PI 3.14159265358979
#define WaveSpeed 1.0
#define CFL 0.15
#define IORDER iOrder
#define IRK iRK
#define INODE iNode
#define IELEM iElem
#define ILENGTH iLength
#define ISTART iStart
#define IFINISH iFinish
#define ITEST iTest
#define ITIME iTime
#define IFLOWNUM iFlowNum
#define IEL_SIZE iEl_Size
#define ICFL iCfl

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ABS(my_val) ((my_val) < 0) ? -(my_val) : (my_val)
#endif
