# Compiler
CC=gcc
# Flags
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -lm -std=c2x

default:
	@echo "Makefile for libppm"
	@echo "Run examples:"
	@echo "make fractal_dragon"
	@echo "make fractal_dragon_cor_random"
	@echo "make fractal_dragon_cor_random_gaussian_blur"
	@echo "make losango"
	@echo "make bandeira_brasil"
	@echo "make blue_waves"
	@echo "make aplica_bitmap_blur"
	@echo "make conway_game_of_life"
	@echo "make escreve_texto"
	@echo "make fractal_estrela"
	@echo "make media_vermelho"
	@echo "make flor"

blue_waves:
	$(CC) -o output/blue_waves examples/blue_waves.c libppm/*.c $(CFLAGS)
	./output/blue_waves

aplica_bitmap_blur:
	$(CC) -o output/aplica_bitmap_blur examples/aplica_bitmap_blur.c libppm/*.c $(CFLAGS)
		./output/blue_waves

fractal_dragon_cor_random_gaussian_blur:
	$(CC) -o output/fractal_dragon_cor_random_gaussian_blur examples/fractal_dragon_cor_random_gaussian_blur.c libppm/*.c $(CFLAGS)
	./output/fractal_dragon_cor_random_gaussian_blur

fractal_dragon_cor_random:
	$(CC) -o output/fractal_dragon_cor_random examples/fractal_dragon_cor_random.c libppm/*.c $(CFLAGS)
	./output/fractal_dragon_cor_random

losango:
	$(CC) -o output/losango examples/losango.c libppm/*.c $(CFLAGS)
	./output/losango

bandeira_brasil:
	$(CC) -o output/bandeira_brasil examples/bandeira_brasil.c libppm/*.c $(CFLAGS)
	./output/bandeira_brasil

conway_game_of_life:
	$(CC) -o output/conway_game_of_life examples/conway_game_of_life.c libppm/*.c $(CFLAGS)
	./output/conway_game_of_life

escreve_texto:
	$(CC) -o output/escreve_texto examples/escreve_texto.c libppm/*.c $(CFLAGS)
	./output/escreve_texto

fractal_estrela:
	$(CC) -o output/fractal_estrela examples/fractal_estrela.c libppm/*.c $(CFLAGS)
	./output/fractal_estrela

media_vermelho:
	$(CC) -o output/media_vermelho examples/media_vermelho.c libppm/*.c $(CFLAGS)
	./output/media_vermelho

flor:
	$(CC) -o output/flor examples/flor.c libppm/*.c $(CFLAGS)
	./output/flor