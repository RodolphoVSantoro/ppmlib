#include "lib/ppmlib.h"
#include "lib/arq.h"
#include <stdio.h>
// #include <time.h>

int main()
{
		// ppm img = cria_ppm(100, 100, verde2);

        ppm img = leitura("imgs/orig.ppm");
        // grava("imgs/backup.ppm", img);

        libera_ppm(img);

        // grava("imgs/descomp.ppm", teste);
        // libera_ppm(teste);

        return 0;
}