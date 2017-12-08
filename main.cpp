//Producer - Customer
#include <omp.h>
#include <cstdio>
#include <fstream>


#include "src\ParalelStuff.cpp" //iostream, ctime
#include "src\Timer.h"
#include "src\mString.h"

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

void readFile(const char* path, std::string& output) {
	std::ifstream stream("code\\main.cpp");
	std::string buf;
	while(getline(stream, buf)) {
		output += buf;
		output += "\n";
	}
}

int main() {
	system("cls");
	
	using namespace TimerNamespace;
	using namespace vez;
	
	srand(time(NULL));
	
	matrix *mat1 = new matrix(30, 30, 5);
	matrix *mat2 = new matrix(30, 30);
	
	//PCParalel *paral = new PCParalel();
	//timer(paral->paraleling(mat2, mat1), paralTimer);

	
	
	/*mString *mstr = new mString("File is opened!");
	writeIntoFile("Logger.txt",mstr);
	*mstr = (const char*)"That's not me!";
	writeIntoFile("Logger.txt",mstr);
	
	int length = fileLength("Logger.txt");
	char* str = new char[length+1];
	str = readFromFile("Logger.txt");
	lo(str);*/
	
	
	
	std::string output;
	readFile("code\\main.cpp", output);
	lo(output);
	
	
	std::cin.get();
	return 0;
}
