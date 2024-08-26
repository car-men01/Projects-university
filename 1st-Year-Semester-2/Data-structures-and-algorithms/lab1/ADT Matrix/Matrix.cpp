#include "Matrix.h"
#include <exception>
#include <iostream>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {

	if (nrLines < 0 || nrCols < 0)
		throw exception();

	this->cols_cap = nrCols + 1;
	this->cols = new int[this->cols_cap];

	this->mat_lines = nrLines;
	this->mat_cols = nrCols;

	this->lines_size = 0;
	this->lines_cap = nrLines; 
	this->lines = new int[this->lines_cap];

	this->values = new TElem[this->lines_cap];

	for (int i = 0; i < this->cols_cap; i++)
		this->cols[i] = 0;

	for (int i = 0; i < this->lines_cap; i++) {
		this->lines[i] = 0;
		this->values[i] = NULL_TELEM;
	}
}
// BC: Theta(1), WC = TC: Theta(nrLines + nrCols)


int Matrix::nrLines() const {

	return this->mat_lines;
}
// BC = WC = TC: Theta(1)

int Matrix::nrColumns() const {

	return this->mat_cols;
}
// BC = WC = TC: Theta(1)

TElem Matrix::element(int i, int j) const {

	if (i < 0 || j < 0 || i >= this->mat_lines || j >= this->mat_cols)
		throw exception();

	int col_start = this->cols[j];
	int col_end = this->cols[j + 1];

	for (int k = col_start; k < col_end; k++) {
		if (this->lines[k] == i)
			return this->values[k];
	}

	// no non-zero element found at position (i, j) 
	return NULL_TELEM;  
}
// BC: Theta(1), WC: Theta(lines_size), TC: O(lines_size)


TElem Matrix::modify(int i, int j, TElem e) {

	if (i < 0 || j < 0 || i >= this->mat_lines || j >= this->mat_cols)
		throw exception();

	int col_start = this->cols[j];
	int col_end = this->cols[j + 1];

	// find the position of element (i, j) in the values array
	int pos = -1;
	for (int k = col_start; k < col_end; k++) {
		if (this->lines[k] == i) {
			pos = k;
			break;
		}
	}

	TElem old_value = NULL_TELEM;

	if (pos != -1) {
		// the position (i, j) exists in the lines array so we save the old value
		old_value = this->values[pos];

		if (e == NULL_TELEM) {
			// decrease the cols array from j + 1
			for (int k = j + 1; k < this->cols_cap; k++) {
				this->cols[k]--;
			}

			// if the new element is 0 remove the element e
			for (int k = pos; k < this->lines_size - 1; k++) {  
				this->values[k] = this->values[k + 1];
				this->lines[k] = this->lines[k + 1];
			}
			this->lines_size--;
		}

		else {
			// if e is not 0 we replace the current element with e
			this->values[pos] = e;
		}
	}

	else {
		// if the old value is NULL_TELEM and the new value is NULL_TELEM 
		if (e == NULL_TELEM)
			return NULL_TELEM;

		// increase the cols array from j + 1
		for (int k = j + 1; k < this->cols_cap; k++) {
			this->cols[k]++;
		}

		if (this->lines_size == this->lines_cap) {
			// resize the dynamic array
			int old_cap = this->lines_cap;
			this->lines_cap = this->lines_cap * 2;

			TElem* array_values = new TElem[this->lines_cap];
			TElem* array_lines = new int[this->lines_cap];

			for (int k = this->lines_size; k < this->lines_cap; k++) {
				array_values[k] = NULL_TELEM;
				array_lines[k] = 0;
			}

			for (int k = 0; k < this->lines_size; k++) {
				array_values[k] = this->values[k];
				array_lines[k] = this->lines[k];
			}

			delete[] this->lines;
			delete[] this->values;

			this->values = array_values;
			this->lines = array_lines;
		}

		// shift the elements to the right
		for (int k = this->lines_size - 1; k >= col_start; k--) {
			this->values[k + 1] = this->values[k];
			this->lines[k + 1] = this->lines[k];
		}

		// the element e doesn't exist so we add it
		this->lines[col_start] = i;
		this->values[col_start] = e;
		this->lines_size++;
	}

	return old_value;
}
// BC: Theta(1), WC: Theta(lines_size + cols_cap), TC: O(lines_size + cols_cap)


int Matrix::numberOfNonZeroElements(int line) const {

	if (line < 0 || line >= this->mat_lines)
		throw exception();

	int cont = 0;

	for (int k = 0; k < this->lines_size; k++) {
		if (this->lines[k] == line)
			cont++;
	}

	return cont;
}
// BC: Theta(1), WC = TC: Theta(lines_size)


Matrix::~Matrix() {
	delete[] this->cols;
	delete[] this->lines;
	delete[] this->values;
}
// BC = WC = TC: Theta(1)
