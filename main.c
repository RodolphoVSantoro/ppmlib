#include "lib/ppmlib.h"
#include "lib/arq.h"
#include <stdio.h>
#include <time.h>

int main(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	
	double delta_us;

	ppm img = leitura("imgs/orig.ppm");
	grava("imgs/backup.ppm",img);

	ppmTodppm("imgs/comp.dppm",img);

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	delta_us = ((end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_nsec - start.tv_nsec) / 1000.0)/1000000.0;
	printf("comprimiu(%lfs)\n",delta_us);
	
	libera_ppm(img);
	
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	ppm teste = dppmToppm("imgs/comp.dppm");
	
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	delta_us = ((end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_nsec - start.tv_nsec) / 1000.0)/1000000.0;
	printf("descomprimiu(%lfs)\n",delta_us);
	
	grava("imgs/descomp.ppm",teste);
	libera_ppm(teste);
	
	return 0;
}
