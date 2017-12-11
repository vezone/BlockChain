#pragma once

#include <iostream>

namespace vez {
	
	struct Data {
		int* m_Buffer;
		short m_Size, m_CurrentIndex;
		
		Data();
		Data(int size);
		
		~Data();
		
		void put(int element);
		int take();
		bool isEmpty();
		
		friend std::ostream& operator<< (std::ostream &stream, const Data& data);
			
	};
	
}
