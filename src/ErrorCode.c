
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
	if (code == ERROR_MATRIX_IS_NULL) {
		return "the matrix you gave is'nt initilize";
	}
	if (code == ERROR_MATRIX_IS_NULL) {
		return "the matrix you gave is'nt initilize";
	}
	if (code == ERROR_MALLOC_FAILED) {
		return "the malloc has failed";
	}
	if (code == ERROR_OUT_OF_MATRIX) {
		return "you tried to get/set a value out of the matrix";
	}
	if (code == ERROR_CANT_CALCULATE) {
		return "the matrixs you gave are impossible to calculate";
	}
	if (code == ERROR_NOT_IMPLEMENTED) {
		return "ERROR_NOT_IMPLEMENTED";
	}
	return "unknown eror";

}
