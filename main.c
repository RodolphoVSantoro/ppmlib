#include <stdio.h>

#include "lib/arq.h"
#include "lib/ppmlib.h"

int main() {
    PPM img = cria_ppm(100, 100, branco);
    libera_ppm(img);
    return 0;
}