#include "matrix.h"

namespace vez {

	//matrix stuff
	matrix::matrix() 
	: m_NumberOfRows(3), m_NumberOfColumns(3), m_Size(9) {
		m_Ptr = new int[m_Size];
		for (int s = 0; s < m_Size; s++) {
			m_Ptr[s] = 0;
		}
	}

	matrix::matrix(int numberOfRows, int numberOfColumns) 
	: m_NumberOfRows(numberOfRows), m_NumberOfColumns(numberOfColumns), m_Size(numberOfRows*numberOfColumns) {
		m_Ptr = new int[m_Size];
		for (int s = 0; s < m_Size; s++) {
			m_Ptr[s] = rand() % 5 + 1;
		}
	}

	matrix::matrix(int numberOfRows, int numberOfColumns, int maxNum) 
	: m_NumberOfRows(numberOfRows),m_NumberOfColumns(numberOfColumns),m_Size(numberOfRows*numberOfColumns)	{
		m_Ptr = new int[m_Size];
		
		for (int s = 0; s < m_Size; s++) {
			int num;
			maxNum += s;
			num = rand() % maxNum + 3;
			m_Ptr[s] = num;
		}

	}

	matrix::~matrix() {
		if (m_Ptr && m_Size > 0)
		   delete[] m_Ptr;
	}

	matrix& matrix::operator=(const matrix& other) { 
	
		m_Size = other.m_Size;
		m_Ptr = new int[m_Size];
		m_NumberOfRows = other.m_NumberOfRows;
		m_NumberOfColumns = other.m_NumberOfColumns;
		
		for (int i = 0; i < m_Size; i++) {
			m_Ptr[i] = other.m_Ptr[i];
		}
		
		return *this;
	}
	

	
	std::ostream& operator<<(std::ostream& stream, const matrix& mat) { //work
		for (int col = 0; col < mat.m_NumberOfColumns; col++) {
			for (int row = 0; row < mat.m_NumberOfRows; row++) {
				stream << mat.m_Ptr[col + row * mat.m_NumberOfRows] << "  ";
			}
			stream << "\n";
		}
		return stream;
	}

}
