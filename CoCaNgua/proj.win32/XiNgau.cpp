#include "XiNgau.h"
#include <time.h>
#include <stdlib.h>

XiNgau::XiNgau(void)
{
	/* initialize random seed: */
  srand ( time(NULL) );
}


XiNgau::~XiNgau(void)
{
}
int XiNgau::next_xoXiNgau(){
	return rand()%6+1;
	//1,2,3,4,5,6
}