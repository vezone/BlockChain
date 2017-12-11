//Producer & Cutomer

#include <iostream>
#include <omp.h>
#include <fstream>
#include <cstring>

#include "matrix.h"
#include "mString.h"
#include "Data.h"

namespace vez {

	struct PCParalel {
		int m_CurrentPosition, m_Flag=0, m_Message;
		mString *m_String;
		omp_lock_t m_Lock;
		
		PCParalel() {
			m_CurrentPosition = 0; 
			m_Flag = 0; 
			m_Message = 0;
			m_String = new mString("__Logger__\n");
		}
		
//1(/3) part of 4 ex		
		void paraleling(matrix *copyTo, matrix *copyFrom) {
			int* bufferVariable = new int[copyFrom->m_Size];
			
			int nprod, ncons, sum;
		
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
		    	
		    	if (m_CurrentPosition >= copyFrom->m_Size)
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
				
				if (m_CurrentPosition >= copyTo->m_Size)
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
		
//2(/3) part of ex 4 
		void paraleling2() {
			std::string bufferVariable;
			
			omp_set_dynamic(0); 	//Запрещяем системе динамически менять количество нитей
		    omp_set_nested(1); 		//Разрешаем вложенный параллелизм
		    omp_init_lock(&m_Lock); 	//Инициализируем замок
		    
		    #pragma omp parallel sections num_threads(2) 
			{
				
				#pragma omp section
			 	{
			        #pragma omp parallel num_threads (2) shared (bufferVariable,m_Flag)
			        producer2(bufferVariable);
			    }
			    
			    #pragma omp section
			    {
			  		#pragma omp parallel num_threads (2) shared (bufferVariable,m_Flag)
			  		consumer2(bufferVariable);
			    }
		    
			}
			
		 	omp_destroy_lock(&m_Lock);
		}
		
		bool producer2(std::string& bufferVariable) {
			srand(time(0));
			std::ifstream stream("code\\main.cpp");
	    	std::string buf;
	    	
		    while (getline(stream, buf)) {
		    	
				while (!omp_test_lock(&m_Lock));//пытаемя перехватить lock, если не выходит, то висим в цикле до перехвата lock'а
				
				if (m_Flag == 0) {
					bufferVariable = buf;
					//printf("\nBufferVariable[%d] = %d.\nFrom: %d\n", m_CurrentPosition, buff, omp_get_thread_num());
					m_Flag++;
				}
				
				omp_unset_lock(&m_Lock);
			}
			
			m_Flag = -1;
			
			return true;
		}
		
		bool consumer2(std::string& bufferVariable) {
	 		std::ifstream stream("code\\main.cpp");
	 		std::string buf;
	 		//mString myString;
	 		
			while (true) {
		    	if (m_Flag == -1)
				   	return true;
					      
				while (!omp_test_lock(&m_Lock));
				
				if (m_Flag > 0) {
					printf("\nBufferVariable: %s\nNumber of threade: %d\n", bufferVariable.c_str(), omp_get_thread_num());
			 		m_Flag--;
				}
				
				omp_unset_lock(&m_Lock);
				
			}
			
			return true;
		}
		
//3(/3) part of ex 4 
		void paraleling3() {
			Data *data = new Data(5);
			int gposition = 0;
			
			omp_set_dynamic(0); 	//Запрещяем системе динамически менять количество нитей
		    omp_set_nested(1); 		//Разрешаем вложенный параллелизм
		    omp_init_lock(&m_Lock); 	//Инициализируем замок
		    
		    #pragma omp parallel sections num_threads(2) 
			{
				
				#pragma omp section
			 	{
			        #pragma omp parallel num_threads (5) shared (data,m_Flag,gposition)
			        producer3(data, gposition);
			    }
			    
			    #pragma omp section
			    {
			  		#pragma omp parallel num_threads (10) shared (data,m_Flag,gposition)
			  		consumer3(data, gposition);
			    }
		    
			}
			
		 	omp_destroy_lock(&m_Lock);
		}
		
		bool producer3(Data* data, int &gposition) {
			
			srand(time(0));
			int num = 0; // чтобы читать с той позиции, на которой мы остановились 
			int *buf = new int[5];
	    	int i;
	    	
		    while (true) {
		    	
		    	while (!omp_test_lock(&m_Lock)); //пытаемя перехватить lock, если не выходит, то висим в цикле до перехвата lock'а
		    	
		    	
		    	if (m_Flag == -1) {
		    		omp_unset_lock(&m_Lock);
					return true;
				}
				
				if (m_Flag == 0) {
				    
				    num = readFilePart("code\\numbers.txt", buf, 5, gposition); 
					if (num == -1) {
						std::cout << "Something goes wrong!\n";
						m_Flag = -1;
						omp_unset_lock(&m_Lock);
						return false;
					}
				    
					//printf("Number: [%d, %d, %d, %d, %d]", buf[0], buf [1], buf[2], buf[3], buf[4]);
					printf("\nBufferVariable(producer): [%d, %d, %d, %d, %d]\n", buf[4], buf[3], buf[2], buf[1], buf[0]);
					for (i = 0; i < 5; i++) {
		  	  			data->put(buf[i]);
					}	
					m_Flag += 5;
				}
				
				omp_unset_lock(&m_Lock);
			}
			
			m_Flag = -1;
			
			return true;
		}
		
		bool consumer3(Data* data, int &gposition) {
	 		int buf;
	 		int i;
	 		
			while (true) {
				
 	 		  	if (m_Flag == -1)
				   	return true;
					      
				while (!omp_test_lock(&m_Lock));
				
				if (m_Flag > 0) {
				   	buf = data->take();   	
					printf("\nBufferVariable(consumer): [%d]\nNumber of thread: %d\n", buf, omp_get_thread_num());
			 		m_Flag--;
				}
				
		  		omp_unset_lock(&m_Lock);
				
			}
			
			return true;
		}
		
	};

}
