#pragma once

//Редактируем matrix 
//

#include <iostream>
#include <cstdio> //c func printf.. printf("%x", num);
#include <ctime>
#include <sstream>
#include <omp.h>

namespace vez {

	struct matrix {
		int m_NumberOfRows, m_NumberOfColumns, m_Size;
		int *m_Ptr = nullptr;
		
		matrix();
		matrix(int numberOfRows, int numberOfColumns);
		matrix(int numberOfRows, int numberOfColumns, int maxNum);
		~matrix();

		matrix& operator= (const matrix& other); 

		friend std::ostream& operator<<(std::ostream& stream, const matrix& mat);
	};

}
