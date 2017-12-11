#include "Data.h"

namespace vez {
	
	Data::Data() {
		m_Buffer = new int[10];
		m_Size = 10;
		for (int i = 0; i < 10; i++) {
			m_Buffer[i] = 0;
		}
		m_CurrentIndex = -1;
	}
	
	Data::Data(int size) {
		m_Buffer = new int[size];
		m_Size = size;
		for (int i = 0; i < size; i++) {
			m_Buffer[i] = 0;
		}
		m_CurrentIndex = -1;
	}
	
	Data::~Data() {
		if (m_Buffer) {
		   if (m_Size >= 0) {
		   	  delete[] m_Buffer;  	
		   }
		   else {
		   	std::cout << "No elements here!" << std::endl;
		   }	
		}
	}
	
	void Data::put(int element) {
		m_CurrentIndex = (m_CurrentIndex >= m_Size) ? -1 : (m_CurrentIndex < 0) ? -1 : m_CurrentIndex;
		m_CurrentIndex++;
		m_Buffer[m_CurrentIndex] = element;
	}
	
	int Data::take() {
		if (m_Size < 0)
		   return -1;
	    
		if (m_CurrentIndex < 0) {
			m_CurrentIndex = 0;
		}
	    
	    int num = m_Buffer[m_CurrentIndex];
	    
		m_Buffer[m_CurrentIndex] = 0;
		m_CurrentIndex--;
		
		if (m_CurrentIndex < 0)
		   m_CurrentIndex = 0;
		   
		return num;
	}
	
	bool Data::isEmpty() {
		bool empty = true;
		for (int i = 0; i < m_Size; i++) {
			if (m_Buffer[i] != 0) {
				empty = false;
			}
		}
		return empty;
	}
	
	std::ostream& operator<< (std::ostream &stream, const Data& data) {
		for (int i = 0; i < data.m_Size; i++)
  			stream << data.m_Buffer[i] << " ";
		return stream;
	}
	
}
