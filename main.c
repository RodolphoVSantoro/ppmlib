#include <stdio.h>

#include "lib/arq.h"
#include "lib/ppmlib.h"

int main() {
    PPM* img = PPM_cria(100, 100, branco);
    PPM_grava("imgs/teste.ppm", img);
    PPM_libera(img);
    return 0;
}