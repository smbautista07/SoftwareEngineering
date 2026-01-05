/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP1001 ------------------------------------------------------------------
------------------COMPUTER SYSTEMS MODULE-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <emmintrin.h>
#include <limits.h>
#include <pmmintrin.h>
#include <immintrin.h>

//function declarations
void edge_detection();
void read_image(char* filename);
void write_image2(char* filename);
void openfile(char* filename, FILE** finput);
int getint(FILE* fp);
void reallocate_memory(int num1, int num2);
void update_file_paths();

//CRITICAL POINT: images' paths - You need to change these paths
//Done

//char IN[] = "C:\\Users\\Sean\\Documents\\GitHub\\SoftwareEngineering\\COMP1001 Tasks\\Assessed\\Assessment 2\\input_images\\a15.pgm";
//char OUT[] = "C:\\Users\\Sean\\Documents\\GitHub\\SoftwareEngineering\\COMP1001 Tasks\\Assessed\\Assessment 2\\output_images\\edge_detection15.pgm";

#define INPUT_FOLDER_PATH "C:\\Users\\Sean\\Documents\\GitHub\\SoftwareEngineering\\COMP1001 Tasks\\Assessed\\Assessment 2\\input_images"
#define OUTPUT_FOLDER_PATH "C:\\Users\\Sean\\Documents\\GitHub\\SoftwareEngineering\\COMP1001 Tasks\\Assessed\\Assessment 2\\output_images"
#define common_input_file_name "a"
#define common_output_file_name "edge_detection"
#define image_count 31
char IN[400];
char OUT[400];

//IMAGE DIMENSIONS
//Change: Magic number for image dimensions are not needed since they are stored in the file and realloc
int N;
int M;

//CRITICAL POINT:these arrays are defined statically. Consider creating these arrays dynamically instead.
//Change: I switched to the C compiler in the settings just to be sure I was using C language only and using malloc here caused an error, so I declared the global pointer here and used malloc in main
unsigned char* input_image;
unsigned char* output_image;

const signed char GxMask[3][3] = {
	{-1,0,1} ,
	{-2,0,2},
	{-1,0,1}
};

const signed char GyMask[3][3] = {
	{-1,-2,-1} ,
	{0,0,0},
	{1,2,1}
};

char header[100];
errno_t err;

int main() {
	//Change: Used malloc to allocate memory dynamically which will allow for array size to be altered for different image sizes. The memory size using malloc does not need to be specified because it is reallocated during read_image.
	input_image = (unsigned char*)malloc(0);
	output_image = (unsigned char*)malloc(0);
	
	for (int index = 0; index < image_count; index++)
	{
		update_file_paths();//Updates the file path to the current image being processed

		read_image(IN);//read image from disc

		edge_detection(); //apply edge detection

		write_image2(OUT); //store output image to the disc

	}
	
	
	free(input_image);
	free(output_image);

	return 0;
}


void update_file_paths()
{
	static int current_index = 0;
	
	//strcat_s could not append "\\" by itself so I had to use snprintf
	/*
	CODE WHICH WAS NOT WORKING
	strcpy_s(IN, 250, INPUT_FOLDER_PATH);
	strcat_s(IN, 2, "\\");
	strcat_s(IN, 140, common_input_file_name);
	strcat_s(IN, 4, current_index);
	strcat_s(IN, 4, ".pgm");

	strcpy_s(OUT, 250, OUTPUT_FOLDER_PATH);
	strcat_s(OUT, 2, "\\");
	strcat_s(OUT, 140, common_output_file_name);
	strcat_s(OUT, 4, current_index);
	strcat_s(OUT, 4, ".pgm");
	*/

	snprintf(IN, 400, "%s//%s%i.pgm", INPUT_FOLDER_PATH, common_input_file_name, current_index);

	snprintf(OUT, 400, "%s//%s%i.pgm", OUTPUT_FOLDER_PATH, common_output_file_name, current_index);

	current_index += 1;
}

void edge_detection() {

	int row, col, rowOffset, colOffset;
	int Gx, Gy;

	//Change: Altered loop paramaters so all pixels are processed rather than ignoring the ones at the edges
	for (row = 0; row < N; row++) {
		for (col = 0; col < M; col++) {

			Gx = 0;
			Gy = 0;

			for (rowOffset = -1; rowOffset <= 1; rowOffset++) {
				for (colOffset = -1; colOffset <= 1; colOffset++) {

					//Change: The selected pixel with its offset is only used in the calculation if it can refer to an actual pixel in the image. If out of bounds, it does not affect the output.
					if ( ( (col + colOffset) >= 0 && (col + colOffset) < M) && ((row + rowOffset) >= 0 && (row + rowOffset) < N))
					{
						Gx += input_image[M * (row + rowOffset) + col + colOffset] * GxMask[rowOffset + 1][colOffset + 1];
						Gy += input_image[M * (row + rowOffset) + col + colOffset] * GyMask[rowOffset + 1][colOffset + 1];
					}
				}
			}

			output_image[M * row + col] = (unsigned char)sqrt(Gx * Gx + Gy * Gy);

		}
	}


}




void read_image(char* filename)
{

	int c;
	FILE* finput;
	int i, j, temp;

	printf("\nReading %s image from disk ...", filename);
	finput = NULL;
	openfile(filename, &finput);

	if ((header[0] == 'P') && (header[1] == '5')) { //if P5 image

		for (j = 0; j < N; j++) {
			for (i = 0; i < M; i++) {

				//if (fscanf_s(finput, "%d", &temp,20) == EOF)
				//	exit(EXIT_FAILURE);
				temp = getc(finput);

				input_image[M * j + i] = (unsigned char)temp;
			}
		}
	}
	else if ((header[0] == 'P') && (header[1] == '2')) { //if P2 image
		for (j = 0; j < N; j++) {
			for (i = 0; i < M; i++) {

				if (fscanf_s(finput, "%d", &temp, 20) == EOF)
					exit(EXIT_FAILURE);

				input_image[M * j + i] = (unsigned char)temp;
			}
		}
	}
	else {
		printf("\nproblem with reading the image");
		exit(EXIT_FAILURE);
	}

	fclose(finput);
	printf("\nimage successfully read from disc\n");

}



void write_image2(char* filename)
{

	FILE* foutput;
	int i, j;



	printf("  Writing result to disk ...\n");

	if ((err = fopen_s(&foutput, filename, "wb")) != NULL) {
		fprintf(stderr, "Unable to open file %s for writing\n", filename);
		exit(-1);
	}

	fprintf(foutput, "P2\n");
	fprintf(foutput, "%d %d\n", M, N);
	fprintf(foutput, "%d\n", 255);

	for (j = 0; j < N; ++j) {
		for (i = 0; i < M; ++i) {
			fprintf(foutput, "%3d ", output_image[M * j + i]);
			if (i % 32 == 31) fprintf(foutput, "\n");
		}
		if (M % 32 != 0) fprintf(foutput, "\n");
	}
	fclose(foutput);


}




void openfile(char* filename, FILE** finput)
{
	int x0, y0, x, aa;

	if ((err = fopen_s(finput, filename, "rb")) != NULL) {
		fprintf(stderr, "Unable to open file %s for reading\n", filename);
		exit(-1);
	}

	aa = fscanf_s(*finput, "%s", header, 20);

	x0 = getint(*finput);//this is M
	y0 = getint(*finput);//this is N
	printf("\t header is %s, while x=%d,y=%d", header, x0, y0);


	//CRITICAL POINT: AT THIS POINT YOU CAN ASSIGN x0,y0 to M,N 
	// printf("\n Image dimensions are M=%d,N=%d",M,N);
	M = x0;
	N = y0;

	reallocate_memory(x0, y0);

	x = getint(*finput); /* read and throw away the range info */
	//printf("\n range info is %d",x);
	
}



//CRITICAL POINT: you can define your routines here that create the arrays dynamically; now, the arrays are defined statically.
//Change: Added a function to reallocate memory based on image size

void reallocate_memory(int new_width, int new_height)
{
	int image_size = new_width * new_height * sizeof(unsigned char);
	input_image = (unsigned char*) realloc(input_image, image_size);
	output_image = (unsigned char*) realloc(output_image, image_size);
	//catches null pointers to prevent memory leaks
	if (input_image == NULL || output_image == NULL) 
	{
		printf("problem with memory allocation");
		free(input_image);
		free(output_image);
		exit(-1);
	}
	
}

int getint(FILE* fp) /* adapted from "xv" source code */
{
	int c, i, firstchar;//, garbage;

	/* note:  if it sees a '#' character, all characters from there to end of
	   line are appended to the comment string */

	   /* skip forward to start of next number */
	c = getc(fp);
	while (1) {
		/* eat comments */
		if (c == '#') {
			/* if we're at a comment, read to end of line */
			char cmt[256], * sp;

			sp = cmt;  firstchar = 1;
			while (1) {
				c = getc(fp);
				if (firstchar && c == ' ') firstchar = 0;  /* lop off 1 sp after # */
				else {
					if (c == '\n' || c == EOF) break;
					if ((sp - cmt) < 250) *sp++ = c;
				}
			}
			*sp++ = '\n';
			*sp = '\0';
		}

		if (c == EOF) return 0;
		if (c >= '0' && c <= '9') break;   /* we've found what we were looking for */

		/* see if we are getting garbage (non-whitespace) */
	   // if (c!=' ' && c!='\t' && c!='\r' && c!='\n' && c!=',')
		//	garbage=1;

		c = getc(fp);
	}

	/* we're at the start of a number, continue until we hit a non-number */
	i = 0;
	while (1) {
		i = (i * 10) + (c - '0');
		c = getc(fp);
		if (c == EOF) return i;
		if (c < '0' || c>'9') break;
	}
	return i;
}







