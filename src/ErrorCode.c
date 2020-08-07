
#include <string.h>

#include "ErrorCode.h"

#define MESSAGE_SIZE 50
#define _CRT_SECURE_NO_WARNINGS

bool error_isSuccess(ErrorCode code) {
	if (code == ERROR_SUCCESS) {
		return true;
	}
	return false;

}

const char* error_getErrorMessage(ErrorCode code) {
	
	if (code == ERROR_SUCCESS) {
		return "no error!:)";
	}
	if (code == MATRIX_IS_NULL) {
		return "the matrix you gave is'nt initilize";
	}
	if (code == MATRIX_IS_NULL) {
		return "the matrix you gave is'nt initilize";
	}
	if (code == MALLOC_FAILED) {
		return "the malloc has failed";
	}
	if (code == OUT_OF_MATRIX_ERROR) {
		return "you tried to get/set a value out of the matrix";
	}
	if (code == CANT_CALCULATE) {
		return "the matrixs you gave are impossible to calculate";
	}
	return "unknown eror";

}
