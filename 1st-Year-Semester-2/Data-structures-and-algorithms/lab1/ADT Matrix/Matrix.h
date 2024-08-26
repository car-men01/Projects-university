#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:

	int* cols;
	int cols_cap;

	int* lines;
	int lines_cap;
	int lines_size;

	int mat_lines;
	int mat_cols;

	TElem* values;



public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//returns the number of non-zero elements from a given line
	//throws an exception if line is not valid
	int numberOfNonZeroElements(int line) const;

	//destructor
	~Matrix();

};
