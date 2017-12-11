//Producer - Customer
#include <omp.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <ctime>

#include "src\ParalelStuff.cpp" //iostream, ctime
#include "src\Timer.h"
#include "src\mString.h"
#include "src\Data.h"

#ifndef log
    #define log(x) std::cout << #x[1] << #x[2] << #x[3] << #x[4] << ":\n" << x << std::endl;
#endif

#ifndef lo
    #define lo(x) std::cout << x << std::endl;
#endif    

#ifndef timer
#define timer(x, var) Timer var;\
				 var.Start();\
				 x;\
				 var.Stop();\
				 var.Print(#var)
#endif


int main() {
	system("cls");
	
	using namespace TimerNamespace;
	using namespace vez;
	
	srand(time(NULL));

//1 part of 4 ex (done)	
//	matrix *mat1 = new matrix(300, 300, 5);
//	matrix *mat2 = new matrix(300, 300);
//	PCParalel *paral = new PCParalel();
//	timer(paral->paraleling(mat2, mat1), paralTimer);
//	lo(*mat1);
//	lo(*mat2);
	
//2 part of 4 ex (done)
	//PCParalel *paral2 = new PCParalel();
	//timer(paral2->paraleling2(), paralTimer2);	
	
//3 part of 4 ex
	//writeFile("code\\numbers.txt", 150);
	PCParalel *paral3 = new PCParalel();
	paral3->paraleling3();
		
	//Пример использования своего файлРидРайтСтафа
	/*int length2 = fileLength("code\\main.cpp");
	char* str2 = new char[length2+1];
	readFromFile("code\\main.cpp", str2);
	mString *mstr = new mString(str2);
	writeIntoFile("code\\maintxt.txt", mstr);
	lo(length2);
//	lo(str2);
	lo(*mstr);*/
	
	
	std::cin.get();
	return 0;
}
