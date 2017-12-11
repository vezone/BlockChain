#pragma once

#include <iostream>
#include <malloc.h>
#include <ctime>

#include "mString.h"

namespace vez {

//class mString
	class mString {
	private:
	
		char* m_String;
		short m_Length;		

	public:
	
		char* getString();
		short getLength();
		void changeString(const char* str);
	public:
	
		mString(char* str);
		mString(const mString& str);
		~mString();
		
		mString& operator= (const char* str);
		mString& operator+= (const char* str);
		friend std::ostream& operator<<(std::ostream& stream, const mString& str);
	
	private:
			
	};

//basic string methodes
	int length(const char* str);
	const char* concat(const char *str1, const char *str2);
	const char* concat(const char *str1, const int number);
	const char* concat(const char *str1, char symbol);
	
	void writeIntoFile(const char* path, mString *str);
	void readFromFile(const char* path, char* buffer);
	int fileLength(const char* path);
	
	//3(/3) for 4 ex
	int returnNumber(int num, std::stringstream &backBuffer, int cur, int last);
	int readFilePart(const char* path, int* number, int partition, int &position);
	bool writeFile(const char* path, int numberOf);
}
