#ifndef PAR_H
#define PAR_H






// functions
int ParameterFile(); // reading in the parameter file so the global variables can be passed 
int AllocateMem();
int GridStuff();
float Basis(int order,float x);
float Basis_X(int order,float x);
float Norms(int iorder);
float InitCond( double x);
float GaussPoints();
float AdvecInit();
int CalculateRHS();
int FluxDriver();
int VolumeFlux();
float RKINT();
int RungeKutta();

#endif
