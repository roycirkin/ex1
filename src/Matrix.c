#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "ErrorCode.h"
#include "Matrix.h"

typedef struct Matrix{
	size_t height;
	size_t width;
	double* ptr;
} Matrix;


// check if the allocate failed
#define CHECK_MATRIX_ALLOC(matrix)                           \
    if ((matrix) == NULL){                                   \
        return ERROR_MALLOC_FAILED;                          \
	}

// check if the given matrix pointer and data pointer are valid
#define CHECK_MATRIX_MEMORY(matrix)                          \
    if ((matrix) == NULL || (matrix)->ptr == NULL) {         \
        return ERROR_MATRIX_IS_NULL;                         \
	}

// check if a matrix function succeseed and stop the program if its not
#define CHECK_MATRIX_CALL(call)                              \
ErrorCode res = (call);                                      \
if (!error_isSuccess(res)) {                                 \
        return res;                                          \
}
	

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    
	matrix_destroy(*matrix);
	*matrix = NULL;

	CHECK_MATRIX_ALLOC(*matrix = (struct Matrix*)malloc(sizeof(struct Matrix)));
	
	(*matrix)->height = height;
	(*matrix)->width = width;

	(*matrix)->ptr = (double*)calloc(height * width, sizeof(double));
	if((*matrix)->ptr == NULL) {
		matrix_destroy(*matrix);
		return ERROR_MALLOC_FAILED;
	}

	
	return ERROR_SUCCESS;

}



ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {

	matrix_destroy(*result);
	*result = NULL;

	CHECK_MATRIX_MEMORY(source);
	
	CHECK_MATRIX_CALL(matrix_create(result, source->height, source->width));

	memcpy((*result)->ptr, source->ptr, source->height * source->width * sizeof(double));

	return ERROR_SUCCESS;
}



void matrix_destroy(PMatrix matrix) {
	if (matrix == NULL) {
		return;
	}
	
	free(matrix->ptr);
	free(matrix);
}



ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {

	CHECK_MATRIX_MEMORY(matrix);

	*result = matrix->height;
	return ERROR_SUCCESS;


	}

	ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
		
	CHECK_MATRIX_MEMORY(matrix);
		

	*result = matrix->width;
	return ERROR_SUCCESS;


	}

	ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
		double value) {
		
		CHECK_MATRIX_MEMORY(matrix);
		

		if (rowIndex >= matrix->height || colIndex >= matrix->width) {
			return ERROR_OUT_OF_MATRIX;
		}

		matrix->ptr[rowIndex * matrix->width + colIndex] = value;
		return ERROR_SUCCESS;


	}

	ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
		double* value) {
		
		CHECK_MATRIX_MEMORY(matrix);
		

		if (rowIndex >= matrix->height || colIndex >= matrix->width) {
			return ERROR_OUT_OF_MATRIX;
		}

		*value = matrix->ptr[rowIndex * matrix->width + colIndex];
		return ERROR_SUCCESS;

	}

	ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
		
 		matrix_destroy(*result);
		*result = NULL;

		CHECK_MATRIX_MEMORY(lhs);
		CHECK_MATRIX_MEMORY(rhs);



		if (lhs->height != rhs->height || lhs->width != rhs->width) {
			return ERROR_CANT_CALCULATE;
		}


		
		CHECK_MATRIX_CALL(matrix_create(result, lhs->height, lhs->width));

		size_t row = 0, col = 0, val = 0;
		double val1 = 0, val2 = 0;
		for (row = 0; row < (*result)->height; row++) {
			for (col = 0; col < (*result)->width; col++) {
				matrix_getValue(lhs, row, col, &val1);
				matrix_getValue(rhs, row, col, &val2);
				val = val1 + val2;
				matrix_setValue(*result, row, col, val);
			}
		}
		return ERROR_SUCCESS;



	}


	ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {

		matrix_destroy(*result);
		*result = NULL;
		
		CHECK_MATRIX_MEMORY(lhs);
		CHECK_MATRIX_MEMORY(rhs);


		if (lhs->width != rhs->height) {
			return ERROR_CANT_CALCULATE;
		}

		
		CHECK_MATRIX_CALL(matrix_create(result, lhs->height, lhs->width));
		

		
		double val1 = 0, val2 = 0, sum = 0;

		for (size_t i = 0; i < lhs->height; i++) {
			for (size_t j = 0; j < rhs->width; j++) {
				for (size_t k = 0; k < lhs->width; k++) {
					matrix_getValue(lhs, i, k, &val1);
					matrix_getValue(rhs, k, j, &val2);
					sum += val1 * val2;
				}
				matrix_setValue(*result, i, j, sum);
				sum = 0;
			}
		}



		return ERROR_SUCCESS;


	}

	ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
		

		CHECK_MATRIX_MEMORY(matrix);


		double temp = 0;
		for (size_t i = 0; i < matrix->height; i++) {
			for (size_t j = 0; j < matrix->width; j++) {
				matrix_getValue(matrix, i, j, &temp);
				matrix_setValue(matrix, i, j, scalar * temp);


			}
		}

		return ERROR_SUCCESS;
				
	}






