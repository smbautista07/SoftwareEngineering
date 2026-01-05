/*
------------------DR VASILIOS KELEFOURAS-----------------------------------------------------
------------------COMP1001 ------------------------------------------------------------------
------------------COMPUTER SYSTEMS MODULE-------------------------------------------------
------------------UNIVERSITY OF PLYMOUTH, SCHOOL OF ENGINEERING, COMPUTING AND MATHEMATICS---
*/


#include <stdio.h> //this library is needed for printf function
#include <stdlib.h> //this library is needed for rand() function
#include <windows.h> //this library is needed for pause() function
#include <time.h> //this library is needed for clock() function
#include <math.h> //this library is needed for abs()
#include <omp.h> //this library is needed for the timer
#include <immintrin.h>

unsigned short int equal(float a, float b); //in C, functions must be declared before main()
void init();
void q1();
void q2();
void q3();
void q1_vec();
void q2_vec();
void q3_vec();


#define N 435 //input size 256 ORIGINALLY
#define EPSILON 1e-6 //relative error margin
#define N_MOD_8 N % 8

float A[N][N], u1[N], u2[N], v1[N], v2[N], x[N], y[N], w[N], z[N];
float alpha = 0.23, beta = 0.45;
__m256 u1_vector, u2_vector, v1_vector, v2_vector, A_vector, w_vector;
__m256 alpha_vector, beta_vector;


int main() {

	double start_1, end_1; //define the timers measuring execution time

	init();//initialize the arrays	
			//Change: Also initialises the alpha and beta vectors

	start_1 = omp_get_wtime(); //start the timer 

	q1();
	q2();
	q3();

	/*q1_vec(); 
	q2_vec();
	q3_vec();*/
	end_1 = omp_get_wtime(); //end the timer 

	printf(" Time in seconds is %f\n", end_1 - start_1 );//print the ex.time
	
	system("pause"); //this command does not let the output window to close

	return 0; //normally, by returning zero, we mean that the program ended successfully. 
}


void init() {

	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) {
			A[i][j] = 0.0f;

		}

	for (i = 0; i < N; i++) {
		u1[i] = (i % 9) * 0.22f;
		u2[i] = (i % 9) * 0.33f;
		v1[i] = (i % 9) * 0.44f;
		v2[i] = (i % 9) * 0.55f;
		w[i] = 0.0f;
	}



	alpha_vector = _mm256_set1_ps(alpha);
	beta_vector = _mm256_set1_ps(beta);
}

void q1() {

	for (int i = 0; i < N; i++) {
		w[i] = alpha * u1[i] + beta; //u stored multiplied by alpha, added onto by beta, then stored in w
	}
}

void q1_vec() 
{

	for (int i = 0; i < N-N_MOD_8; i += 8)
	{
		u1_vector = _mm256_load_ps(&u1[i]);
		u1_vector = _mm256_fmadd_ps(u1_vector, alpha_vector, beta_vector);
		_mm256_store_ps(&w[i], u1_vector);
	}

	for (int i = N - N_MOD_8; i < N; i++) 
	{
		w[i] = alpha * u1[i] + beta; 
	}
}

void q2() {

	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];

}

void q2_vec()
{
	for (int i = 0; i < N; i++)
	{
		u1_vector = _mm256_set1_ps(u1[i]);	//These two only update when 'i' updates so it is a waste of resources for them to be in the second nested loop
		u2_vector = _mm256_set1_ps(u2[i]);
		for (int j = 0; j < N - N_MOD_8; j += 8)
		{
			A_vector = _mm256_load_ps(&A[i][j]);
			v1_vector = _mm256_load_ps(&v1[j]);
			v2_vector = _mm256_load_ps(&v2[j]);

			v1_vector = _mm256_fmadd_ps(u1_vector, v1_vector, A_vector); //Original value of A is needed since using the += rather than the = operator
			v2_vector = _mm256_fmadd_ps(u2_vector, v2_vector, v1_vector);

			_mm256_store_ps(&A[i][j], v2_vector);
		}
		
		for (int j = N - N_MOD_8; j < N; j++)
		{
			A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
		}
		
	}

	/*for (int i = N-N_MOD_8; i < N; i++)
		for (int j = 0; j < N; j++)
			A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];*/
	
}

void q3() {

	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			w[i] += alpha * A[i][j] * u1[j];

}

void q3_vec()
{
	int i, j;
	__m256 empty_vector = _mm256_set1_ps(0);
	float array[8];

	for (i = 0; i < N; i++)
	{
		__m256 temp_vector = _mm256_set1_ps(0); //Initialise a vector with empty values
		
		for (j = 0; j < N - N_MOD_8; j+=8)
		{
			A_vector = _mm256_load_ps(&A[i][j]);
			u1_vector = _mm256_load_ps(&u1[j]);
			temp_vector = _mm256_fmadd_ps(u1_vector, A_vector, temp_vector);
		}

		//Horizontal add three times with to sum all the values in the first and fifth elements
		temp_vector = _mm256_hadd_ps(temp_vector, empty_vector);
		temp_vector = _mm256_hadd_ps(temp_vector, empty_vector);
		temp_vector = _mm256_hadd_ps(temp_vector, empty_vector);

		temp_vector = _mm256_mul_ps(temp_vector, alpha_vector);

		_mm256_store_ps(array, temp_vector);
		
		w[i] += array[0]; //Extract values from arrays and add to total
		w[i] += array[4];
		

		//The j values which do not fit into the intrinsic vectors are calculated seperately.
		for (j = N-N_MOD_8 ; j < N; j++)
		{
			w[i] += alpha * A[i][j] * u1[j];
		}
	}
}

//this function becomes problematic when b is zero or when both a and b are zero
unsigned short int equal(float a, float b) {
	float temp = a - b;

	if (fabs(temp / b) < EPSILON)
		return 0; //success
	else
		return 1; //wrong result
}