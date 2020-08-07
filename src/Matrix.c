#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "ErrorCode.h"
#include "Matrix.h"
#include "Matrix_impl.h"

typedef struct Matrix{
size_t height;
sixe_t width;
double* ptr;

} Matrix;




ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    
	 matrix_destroy(*matrix);

	*matrix = (struct Matrix*)malloc(sizeof(struct Matrix));
	if ((*matrix) == NULL) {
		return MALLOC_FAILED;
	}
	(*matrix)->height = height;
	(*matrix)->width = width;

	(*matrix)->ptr = (double*)calloc(height * width, sizeof(double));
	if ((*matrix)->ptr == NULL) {
		matrix_destroy(*matrix);
		*matrix = NULL;
		return MALLOC_FAILED;
	}

	return ERROR_SUCCESS;

}



ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {

	 matrix_destroy(*result);

	if (source == NULL) {
		return MATRIX_IS_NULL;
	}
	if (source->ptr == NULL) {
		return MATRIX_IS_NULL;
	}

	ErrorCode res;
	res = matrix_create(result, source->height, source->width);
	if (res != ERROR_SUCCESS) {
		return res;
	}

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
		if (matrix == NULL) {
			return MATRIX_IS_NULL;
		}
		*result = matrix->height;
		return ERROR_SUCCESS;


	}

	ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
		if (matrix == NULL) {
			return MATRIX_IS_NULL;
		}
		*result = matrix->width;
		return ERROR_SUCCESS;


	}

	ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
		double value) {

		if (matrix == NULL) {
			return MATRIX_IS_NULL;
		}

		if (rowIndex >= matrix->height || colIndex >= matrix->width) {
			return OUT_OF_MATRIX_ERROR;
		}

		matrix->ptr[rowIndex * matrix->width + colIndex] = value;
		return ERROR_SUCCESS;


	}

	ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
		double* value) {

		if (matrix == NULL) {
			return MATRIX_IS_NULL;
		}

		if (rowIndex >= matrix->height || colIndex >= matrix->width) {
			return OUT_OF_MATRIX_ERROR;
		}

		*value = matrix->ptr[rowIndex * matrix->width + colIndex];
		return ERROR_SUCCESS;

	}
	/////////////////////////////////////////////////////////////////free beshgioot vebaklali

	ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
		
 		matrix_destroy(*result);

		if (lhs == NULL || rhs == NULL) {
			return MATRIX_IS_NULL;
		}
		if ((lhs->ptr) == NULL || (rhs->ptr) == NULL) {
			return MATRIX_IS_NULL;
		}


		if (lhs->height != rhs->height || lhs->width != rhs->width) {
			return CANT_CALCULATE;
		}


		ErrorCode res;
		res = matrix_create(result, lhs->height, lhs->width);
		if (res != ERROR_SUCCESS) {
			return res;
		}


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

	double multipyVectors(double* v1, double* v2, size_t length) {


		double sum = 0;
		for (size_t i = 0; i < length; i++) {
			sum += v1[i] * v2[i];
		}
		return sum;

	}

	ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {

		matrix_destroy(*result);

		if (lhs == NULL || rhs == NULL) {
			return MATRIX_IS_NULL;
		}
		if ((lhs->ptr) == NULL || (rhs->ptr) == NULL) {
			return MATRIX_IS_NULL;
		}

		if (lhs->width != rhs->height) {
			return CANT_CALCULATE;
		}

		ErrorCode res;
		res = matrix_create(result, lhs->height, lhs->width);
		if (res != ERROR_SUCCESS) {
			return res;
		}

		
		double val1 = 0, val2 = 0, sum = 0;

		for (size_t i = 0; i < lhs->height; i++) {
			for (size_t j = 0; i < rhs->width; j++) {
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
		if (matrix == null) {
			return MATRIX_IS_NULL;
		}
		if ((matrix->ptr) == NULL) {
			return MATRIX_IS_NULL;
		}

		double temp = 0;
		for (size_t i = 0; i < lhs->height; i++) {
			for (size_t j = 0; i < rhs->width; j++) {
				matrix_setValue(matrix, i, j, scalar * matrix_getValue(matrix, i, j, &temp));


			}
		}

		return ERROR_SUCCESS;
				
	}






