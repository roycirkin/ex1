# ex1


ex1 was about producing a shared libary which will be used in dynamically linking. 
the libary is called libMatrix and it contains the following functions:

- matrix_create
- matrix_copy
- matrix_destroy
- matrix_getHeight
- matrix_getWidth
- matrix_getValue
- matrix_setValue
- matrix_add
- matrix_multiplyMatrices
- matrix_multipyWithScalar

# implementation

- the implementation of the struct matrix is by holding its height and width
and a pointer to the matrix-table itself as well
- most of the implementation is based on getting and setting the values from the
matrix-table by entering the row and the column of the wanted value
- the function "matrix_add" is calculating the sum of the two values from the
wanted matrix which are located in the same place and putting it into the new matrix in the same location.
- matrix_multiplyMatrices is calculating the double of the i row with the j column
and setting this double into the new matrix in the cell of i,j.
- matrix_multiplyWithScalar is multiplier each of the value in the matrix with the given scalar.

# the tests I made:

first of all, I ran a few short tests for each of the different functions separately.
then I started checking if a series of actions on the matrix returns the right result.
then I ran the tester file which was given to us and saw that everything works as expected
and nothing makes the libary collapse or having it a run time exception.
