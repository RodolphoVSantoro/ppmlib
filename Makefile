# Compiler
CC=gcc
# Flags
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -lm -std=c2x
# include folder
INCLUDE=-Ilibppm
#output folder
OUTPUT=output
EXAMPLES=examples
LIB=libppm

default:
	@echo "Makefile for libppm"
	@echo "Run examples:"
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
	@echo "make beach"
	@echo "make overlay"
	@echo "make chessboard"

blue_waves:
	$(CC) -o $(OUTPUT)/blue_waves $(INCLUDE) $(EXAMPLES)/blue_waves.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/blue_waves

aplica_bitmap_blur:
	$(CC) -o $(OUTPUT)/aplica_bitmap_blur $(INCLUDE) $(EXAMPLES)/aplica_bitmap_blur.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/aplica_bitmap_blur

fractal_dragon_cor_random_gaussian_blur:
	$(CC) -o $(OUTPUT)/fractal_dragon_cor_random_gaussian_blur $(INCLUDE) $(EXAMPLES)/fractal_dragon_cor_random_gaussian_blur.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/fractal_dragon_cor_random_gaussian_blur

fractal_dragon_cor_random:
	$(CC) -o $(OUTPUT)/fractal_dragon_cor_random $(INCLUDE) $(EXAMPLES)/fractal_dragon_cor_random.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/fractal_dragon_cor_random

losango:
	$(CC) -o $(OUTPUT)/losango $(INCLUDE) $(EXAMPLES)/losango.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/losango

bandeira_brasil:
	$(CC) -o $(OUTPUT)/bandeira_brasil $(INCLUDE) $(EXAMPLES)/bandeira_brasil.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/bandeira_brasil

conway_game_of_life:
	$(CC) -o $(OUTPUT)/conway_game_of_life $(INCLUDE) $(EXAMPLES)/conway_game_of_life.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/conway_game_of_life

escreve_texto:
	$(CC) -o $(OUTPUT)/escreve_texto $(INCLUDE) $(EXAMPLES)/escreve_texto.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/escreve_texto

fractal_estrela:
	$(CC) -o $(OUTPUT)/fractal_estrela $(INCLUDE) $(EXAMPLES)/fractal_estrela.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/fractal_estrela

media_vermelho:
	$(CC) -o $(OUTPUT)/media_vermelho $(INCLUDE) $(EXAMPLES)/media_vermelho.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/media_vermelho

flor:
	$(CC) -o $(OUTPUT)/flor $(INCLUDE) $(EXAMPLES)/flor.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/flor

beach:
	$(CC) -o $(OUTPUT)/beach $(INCLUDE) $(EXAMPLES)/beach_downsize.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/beach

overlay:
	$(CC) -o $(OUTPUT)/overlay $(INCLUDE) $(EXAMPLES)/overlay.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/overlay

chessboard:
	$(CC) -o $(OUTPUT)/chessboard $(INCLUDE) $(EXAMPLES)/xadrez.c $(LIB)/*.c $(CFLAGS)
	./$(OUTPUT)/chessboard