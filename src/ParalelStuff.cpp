//Producer & Cutomer

#include <iostream>
#include <omp.h>

#include "matrix.h"
#include "mString.h"

namespace vez {

	struct PCParalel {
		int m_CurrentPosition, m_Flag, m_Message;
		mString *m_String;
		omp_lock_t m_Lock;
		
		PCParalel() {
			m_CurrentPosition = 0; 
			m_Flag = 0; 
			m_Message = 0;
			m_String = new mString("__Logger__\n");
		}
		
		void paraleling(matrix *copyTo, matrix *copyFrom) {
			int* bufferVariable = new int[copyFrom->m_Size];
			
			int nprod, ncons;
		
			std::cout << "Write number of producers:"; std::cin >> nprod;
			std::cout << "Write number of consumers:"; std::cin >> ncons;
			
			
			omp_set_dynamic(0); 	//Запрещяем системе динамически менять количество нитей
		    omp_set_nested(1); 		//Разрешаем вложенный параллелизм
		    omp_init_lock(&m_Lock); 	//Инициализируем замок
		    
		    #pragma omp parallel sections num_threads(2) 
			{
				
				#pragma omp section
			 	{
			        #pragma omp parallel num_threads (nprod) shared (m_CurrentPosition,m_Message,bufferVariable,m_Flag)
			        producer(bufferVariable, copyFrom);
			    }
			    
			    #pragma omp section
			    {
			  		#pragma omp parallel num_threads (ncons) shared (m_CurrentPosition,m_Message,bufferVariable,m_Flag)
			  		consumer(bufferVariable, copyTo);
			    }
		    
			}
			
		 	omp_destroy_lock(&m_Lock);
		}
		
		bool producer(int* bufferVariable, matrix *copyFrom) {
			srand(time(0));
	    
		    while (true) {
		    	
		    	if (m_CurrentPosition >= copyFrom->m_Size - 1)
		    	   return true;
		    	
				while (!omp_test_lock(&m_Lock));//пытаемя перехватить lock, если не выходит, то висим в цикле до перехвата lock'а
				
				if (m_Flag == 0) {
					int buff = copyFrom->m_Ptr[m_CurrentPosition];
					bufferVariable[m_CurrentPosition] = buff;
					
					//printf("\nBufferVariable[%d] = %d.\nFrom: %d\n", m_CurrentPosition, buff, omp_get_thread_num());
					
					m_CurrentPosition++;
					m_Flag++;
				}	
				
				omp_unset_lock(&m_Lock);
			}
			
			return true;
		}
		
		bool consumer(int* bufferVariable, matrix *copyTo) {
		
			while (true) {
				
				if (m_CurrentPosition >= copyTo->m_Size - 1)
		    	   return true;
		    	   
				while (!omp_test_lock(&m_Lock));
				
				if (m_Flag > 0) {
					int buff = bufferVariable[m_CurrentPosition - 1];
		 	        copyTo->m_Ptr[m_CurrentPosition - 1] = buff;
					//printf("\nm_Ptr[%d] = %d.\n", m_CurrentPosition-1, buff, omp_get_thread_num());
			 		m_Flag--;
				}
				
				omp_unset_lock(&m_Lock);
				
			}
			
			return true;
		}
		
		
	};

}
