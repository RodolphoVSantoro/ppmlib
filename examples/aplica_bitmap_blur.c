#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../libppm/libdesenho.h"
#include "../libppm/libefeito.h"
#include "../libppm/libppm.h"

int main() {
    PPM* img = PPM_leitura("imgs/blue_waves.ppm");

    efeito_aplica_negativo(&img);
    efeito_aplica_bitmap(&img);
    efeito_aplica_blur_gaussiano(&img, 10);

    PPM_grava("imgs/bitmap_blur.ppm", img);
    PPM_libera(img);
    return 0;
}
