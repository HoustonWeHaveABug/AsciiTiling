#include <stdio.h>
#include <stdlib.h>

#define TILING_SIZE 2
#define ROTATIONS_N (TILING_SIZE*TILING_SIZE)
#define MATRIX_SIZE 8
#define PIECES_N 95

typedef struct {
	int symbol;
	int rotations[ROTATIONS_N][MATRIX_SIZE];
}
piece_t;

void set_tile_rotation(int *, int *);
void set_matrix_rotation(int [], int []);
void copy_bit(int [], int, int, int [], int, int);
int get_bit(int [], int, int);
void set_bit(int [], int, int, int);
void free_tiles(int *[], int);

piece_t pieces[PIECES_N] = {
	{ ' ', { { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '!', { { 8, 8, 8, 8, 0, 0, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '\"', { { 20, 20, 0, 0, 0, 0, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '#', { { 20, 20, 62, 20, 62, 20, 20, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '$', { { 8, 60, 10, 28, 40, 30, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '%', { { 6, 38, 16, 8, 4, 50, 48, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '&', { { 12, 18, 10, 4, 42, 18, 44, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '\'', { { 12, 8, 4, 0, 0, 0, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '(', { { 16, 8, 4, 4, 4, 8, 16, 0 }, { 0 }, { 0 }, { 0 } } },
	{ ')', { { 4, 8, 16, 16, 16, 8, 4, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '*', { { 0, 8, 42, 28, 42, 8, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '+', { { 0, 8, 8, 62, 8, 8, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ ',', { { 0, 0, 0, 0, 12, 8, 4, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '-', { { 0, 0, 0, 62, 0, 0, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '.', { { 0, 0, 0, 0, 0, 12, 12, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '/', { { 0, 32, 16, 8, 4, 2, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '0', { { 28, 34, 50, 42, 38, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '1', { { 8, 12, 8, 8, 8, 8, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '2', { { 28, 34, 32, 16, 8, 4, 62, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '3', { { 62, 16, 8, 16, 32, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '4', { { 16, 24, 20, 18, 62, 16, 16, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '5', { { 62, 2, 30, 32, 32, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '6', { { 24, 4, 2, 30, 34, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '7', { { 62, 32, 16, 8, 4, 4, 4, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '8', { { 28, 34, 34, 28, 34, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '9', { { 28, 34, 34, 60, 32, 16, 12, 0 }, { 0 }, { 0 }, { 0 } } },
	{ ':', { { 0, 12, 12, 0, 12, 12, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ ';', { { 0, 12, 12, 0, 12, 8, 4, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '<', { { 16, 8, 4, 2, 4, 8, 16, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '=', { { 0, 0, 62, 0, 62, 0, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '>', { { 4, 8, 16, 32, 16, 8, 4, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '?', { { 28, 34, 32, 16, 8, 0, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '@', { { 28, 34, 32, 44, 42, 42, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'A', { { 28, 34, 34, 34, 62, 34, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'B', { { 30, 34, 34, 30, 34, 34, 30, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'C', { { 28, 34, 2, 2, 2, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'D', { { 14, 18, 34, 34, 34, 18, 14, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'E', { { 62, 2, 2, 30, 2, 2, 62, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'F', { { 62, 2, 2, 30, 2, 2, 2, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'G', { { 28, 34, 2, 58, 34, 34, 60, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'H', { { 34, 34, 34, 62, 34, 34, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'I', { { 28, 8, 8, 8, 8, 8, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'J', { { 56, 16, 16, 16, 16, 18, 12, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'K', { { 34, 18, 10, 6, 10, 18, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'L', { { 2, 2, 2, 2, 2, 2, 62, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'M', { { 34, 54, 42, 42, 34, 34, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'N', { { 34, 34, 38, 42, 50, 34, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'O', { { 28, 34, 34, 34, 34, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'P', { { 30, 34, 34, 30, 2, 2, 2, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'Q', { { 28, 34, 34, 34, 42, 18, 44, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'R', { { 30, 34, 34, 30, 10, 18, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'S', { { 60, 2, 2, 28, 32, 32, 30, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'T', { { 62, 8, 8, 8, 8, 8, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'U', { { 34, 34, 34, 34, 34, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'V', { { 34, 34, 34, 34, 34, 20, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'W', { { 34, 34, 34, 42, 42, 42, 20, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'X', { { 34, 34, 20, 8, 20, 34, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'Y', { { 34, 34, 34, 20, 8, 8, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'Z', { { 62, 32, 16, 8, 4, 2, 62, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '[', { { 28, 4, 4, 4, 4, 4, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '\\', { { 0, 2, 4, 8, 16, 32, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ ']', { { 28, 16, 16, 16, 16, 16, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '^', { { 8, 20, 34, 0, 0, 0, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '_', { { 0, 0, 0, 0, 0, 0, 62, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '`', { { 4, 8, 16, 0, 0, 0, 0, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'a', { { 0, 0, 28, 32, 60, 34, 60, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'b', { { 2, 2, 2, 30, 34, 34, 30, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'c', { { 0, 0, 60, 2, 2, 2, 60, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'd', { { 32, 32, 32, 60, 34, 34, 60, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'e', { { 0, 0, 28, 34, 62, 2, 60, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'f', { { 16, 40, 8, 28, 8, 8, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'g', { { 0, 0, 60, 34, 60, 32, 30, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'h', { { 2, 2, 2, 30, 34, 34, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'i', { { 0, 8, 0, 8, 8, 8, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'j', { { 16, 0, 16, 16, 16, 18, 12, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'k', { { 4, 4, 36, 20, 12, 20, 36, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'l', { { 12, 8, 8, 8, 8, 8, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'm', { { 0, 0, 54, 42, 42, 42, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'n', { { 0, 0, 26, 38, 34, 34, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'o', { { 0, 0, 28, 34, 34, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'p', { { 0, 0, 30, 34, 30, 2, 2, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'q', { { 0, 0, 60, 34, 60, 32, 32, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'r', { { 0, 0, 26, 38, 2, 2, 2, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 's', { { 0, 0, 60, 2, 28, 32, 30, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 't', { { 8, 8, 62, 8, 8, 40, 16, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'u', { { 0, 0, 34, 34, 34, 34, 28, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'v', { { 0, 0, 34, 34, 34, 20, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'w', { { 0, 0, 34, 34, 42, 42, 20, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'x', { { 0, 0, 34, 20, 8, 20, 34, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'y', { { 0, 0, 34, 20, 8, 8, 4, 0 }, { 0 }, { 0 }, { 0 } } },
	{ 'z', { { 0, 0, 62, 16, 8, 4, 62, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '{', { { 24, 4, 4, 2, 4, 4, 24, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '|', { { 8, 8, 8, 8, 8, 8, 8, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '}', { { 12, 16, 16, 32, 16, 16, 12, 0 }, { 0 }, { 0 }, { 0 } } },
	{ '~', { { 32, 28, 2, 0, 0, 0, 0, 0 }, { 0 }, { 0 }, { 0 } } }
};
int tile_size;

int main(void) {
	int square_size, rotations_offset, tile_area, *tiles[ROTATIONS_N], row, pieces_idx, rotations_idx, tiling[ROTATIONS_N], canvas_size;
	if (scanf("%d%d%d", &square_size, &rotations_offset, &tile_size) != 3 || square_size < 1 || rotations_offset < 0 || rotations_offset >= ROTATIONS_N || tile_size < 1) {
		fprintf(stderr, "Invalid tiling settings\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	if (getchar() != '\n') {
		fprintf(stderr, "Invalid input\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	tile_area = tile_size*tile_size;
	tiles[0] = malloc(sizeof(int)*(size_t)tile_area);
	if (!tiles[0]) {
		fprintf(stderr, "Could not allocate memory for tiles[0]\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	for (row = 0; row < tile_size; row++) {
		int column;
		for (column = 0; column < tile_size; column++) {
			int symbol = getchar();
			for (pieces_idx = 0; pieces_idx < PIECES_N && pieces[pieces_idx].symbol != symbol; pieces_idx++);
			if (pieces_idx == PIECES_N) {
				fprintf(stderr, "Invalid piece\n");
				fflush(stderr);
				free_tiles(tiles, 1);
				return EXIT_FAILURE;
			}
			tiles[0][row*tile_size+column] = pieces_idx;
		}
		if (getchar() != '\n') {
			fprintf(stderr, "Invalid input\n");
			fflush(stderr);
			free_tiles(tiles, 1);
			return EXIT_FAILURE;
		}
	}
	for (rotations_idx = 1; rotations_idx < ROTATIONS_N; rotations_idx++) {
		tiles[rotations_idx] = malloc(sizeof(int)*(size_t)tile_area);
		if (!tiles[rotations_idx]) {
			fprintf(stderr, "Could not allocate memory for tiles[%d]\n", rotations_idx);
			fflush(stderr);
			free_tiles(tiles, rotations_idx);
			return EXIT_FAILURE;
		}
		set_tile_rotation(tiles[rotations_idx-1], tiles[rotations_idx]);
	}
	for (pieces_idx = 0; pieces_idx < PIECES_N; pieces_idx++) {
		for (rotations_idx = 1; rotations_idx < ROTATIONS_N; rotations_idx++) {
			set_matrix_rotation(pieces[pieces_idx].rotations[rotations_idx-1], pieces[pieces_idx].rotations[rotations_idx]);
		}
	}
	tiling[0] = 0;
	tiling[1] = rotations_offset;
	tiling[3] = (tiling[1]+rotations_offset)%ROTATIONS_N;
	tiling[2] = (tiling[3]+rotations_offset)%ROTATIONS_N;
	puts("<!DOCTYPE HTML>");
	puts("<HTML DIR=\"ltr\" LANG=\"en\">");
	puts("<HEAD>");
	puts("<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; CHARSET=utf-8\">");
	puts("<TITLE>ASCII Tiling</TITLE>");
	puts("<STYLE TYPE=\"text/css\">");
	puts("BODY { font-family: Courier; }");
	puts("H1 { font-size: 16px; }");
	puts("P { font-size: 12px; }");
	puts("TABLE { border-collapse: collapse; }");
	puts("TD { border: 0px; }");
	for (rotations_idx = 0; rotations_idx < ROTATIONS_N; rotations_idx++) {
		printf("TD.f%d { background-color: #%06x; height: 1px; width: 1px; }\n", rotations_idx, (rotations_idx+11)*0x111111);
	}
	puts("TD.t { background-color: #000000; height: 1px; width: 1px; }");
	puts("</STYLE>");
	puts("</HEAD>");
	puts("<BODY>");
	puts("<H1>");
	puts("<A HREF=\"https://www.reddit.com/r/dailyprogrammer/comments/8ylltu/20180713_challenge_365_hard_tessellations_and/\" TARGET=\"_blank\">ASCII Tiling</A>");
	puts("</H1>");
	puts("<TABLE>");
	puts("<CAPTION>");
	printf("Square size %d<BR>\n", square_size);
	printf("Rotations offset %d<BR>\n", rotations_offset);
	printf("Tile size %d<BR>\n", tile_size);
	puts("</CAPTION>");
	canvas_size = MATRIX_SIZE*tile_size*TILING_SIZE*square_size;
	for (row = 0; row < canvas_size; row++) {
		int matrix_row = row%MATRIX_SIZE, tile_row = row%(MATRIX_SIZE*tile_size)/MATRIX_SIZE, tiling_row = row%(MATRIX_SIZE*tile_size*TILING_SIZE)/(MATRIX_SIZE*tile_size), column;
		puts("<TR>");
		for (column = 0; column < canvas_size; column++) {
			int matrix_column = column%MATRIX_SIZE, tile_column = column%(MATRIX_SIZE*tile_size)/MATRIX_SIZE, tiling_column = column%(MATRIX_SIZE*tile_size*TILING_SIZE)/(MATRIX_SIZE*tile_size), rotations_n = tiling[tiling_row*TILING_SIZE+tiling_column];
			if (get_bit(pieces[tiles[rotations_n][tile_row*tile_size+tile_column]].rotations[rotations_n], matrix_row, matrix_column)) {
				puts("<TD CLASS=\"t\"/>");
			}
			else {
				printf("<TD CLASS=\"f%d\"/>\n", rotations_n);
			}
		}
		puts("</TR>");
	}
	puts("</TABLE>");
	puts("</BODY>");
	puts("</HTML>");
	free_tiles(tiles, ROTATIONS_N);
	return EXIT_SUCCESS;
}

void set_tile_rotation(int *tile_a, int *tile_b) {
	int half = tile_size/2+tile_size%2, row;
	for (row = 0; row < half; row++) {
		int column;
		for (column = 0; column < half; column++) {
			tile_b[column*tile_size+tile_size-1-row] = tile_a[row*tile_size+column];
			tile_b[(tile_size-1-row)*tile_size+tile_size-1-column] = tile_a[column*tile_size+tile_size-1-row];
			tile_b[(tile_size-1-column)*tile_size+row] = tile_a[(tile_size-1-row)*tile_size+tile_size-1-column];
			tile_b[row*tile_size+column] = tile_a[(tile_size-1-column)*tile_size+row];
		}
	}
}

void set_matrix_rotation(int matrix_a[], int matrix_b[]) {
	int half = MATRIX_SIZE/2+MATRIX_SIZE%2, row;
	for (row = 0; row < half; row++) {
		int column;
		for (column = 0; column < half; column++) {
			copy_bit(matrix_a, row, column, matrix_b, column, MATRIX_SIZE-1-row);
			copy_bit(matrix_a, column, MATRIX_SIZE-1-row, matrix_b, MATRIX_SIZE-1-row, MATRIX_SIZE-1-column);
			copy_bit(matrix_a, MATRIX_SIZE-1-row, MATRIX_SIZE-1-column, matrix_b, MATRIX_SIZE-1-column, row);
			copy_bit(matrix_a, MATRIX_SIZE-1-column, row, matrix_b, row, column);
		}
	}
}

void copy_bit(int matrix_a[], int row_a, int column_a, int matrix_b[], int row_b, int column_b) {
	set_bit(matrix_b, row_b, column_b, get_bit(matrix_a, row_a, column_a));
}

int get_bit(int matrix[], int row, int column) {
	return matrix[row] & (1 << column) ? 1:0;
}

void set_bit(int matrix[], int row, int column, int bit) {
	matrix[row] |= bit << column;
}

void free_tiles(int *tiles[], int rotations_n) {
	int rotations_idx;
	for (rotations_idx = 0; rotations_idx < rotations_n; rotations_idx++) {
		free(tiles[rotations_idx]);
	}
}
