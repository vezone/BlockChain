#include <cstring>
#include <sstream>
#include <memory>
#include <cstdio>

#include "mString.h"

namespace vez {
	
	
//class mString
	mString::mString(char* str) {
		m_Length = length(str);
		m_String = (char*) malloc((m_Length + 1) * sizeof(char));
		memcpy((void*)m_String, str, m_Length);
		m_String[m_Length] = '\0';
	}
	
	mString::mString(const mString& str) {
		m_String = str.m_String;
		m_Length = str.m_Length;
	}
	
	mString::~mString() {
		if (m_String && m_Length > 0)
		   delete[] m_String;
	}
	
	char* mString::getString() {
		return m_String;
	}
	
	short mString::getLength() {
		return m_Length;
	}
	
	mString& mString::operator= (const char* str) {
		m_Length = length(str);
		m_String = (char*) malloc((m_Length + 1) * sizeof(char));
		for (int i = 0; i < m_Length; i++) {
			m_String[i] = str[i];
		}
		m_String[m_Length] = '\0';
		return *this;
	}
	
	mString& mString::operator+=(const char* str) {
		int sLength = length(str),
			oLength = getLength(),
			summary = sLength + oLength;
		
		mString newString(m_String);
		m_String = new char(summary + 1);
		m_Length = summary + 1;
		
		//return old 
		for (int i = 0; i < oLength; i++) {
			std::cout << "Copy1 i: " << i << std::endl;
			m_String[i] = newString.m_String[i];
		}
		
		//add new
		for (int i = oLength; i < summary; i++) {
			std::cout << "Copy2 i: " << i << std::endl;
			m_String[i] = str[i-oLength]; 
		}
		
		//null determinant
		m_String[summary] = '\0';
		
		return *this;
	}
	
	//mString& mString::operator+ () {}
	std::ostream& operator<<(std::ostream& stream, const mString& str) { //work	
		return stream << str.m_String;
	}

	
//basic string methodes	
	int length(const char* str) {
		int length = 0;
		for (int i = 0; str[i] != '\0'; i++) {
			length++;
		}
		return length;
	}	
	
	const char* concat(const char *str1, const char *str2) {
		int length1 = length(str1),
			length2 = length(str2),
		sum = length1 + length2;
	
		char *finalString = (char*)malloc((sum+1)*sizeof(char));
		
		for (int i = 0; i < length1; i++) {
			finalString[i] = str1[i];
		}
		
		for (int i = length1, j = 0; i < sum; i = i + 1, j = j + 1) {
			finalString[i] = str2[j]; 
		}

		finalString[sum] = '\0';
	
		return (const char*)finalString;
	}
	
	const char* concat(const char *str1, const int number) {

		std::stringstream ss;
		ss << number;
		std::string s = ss.str();
		const char* str3 = s.c_str();
		
		int length1 = length(str1),
			length2 = length(str3),
			sum = length1 + length2;

		char *finalString = (char*)malloc((sum + 1)*sizeof(char));

		for (int i = 0; i < length1; i++) {
			finalString[i] = str1[i];
		}

		for (int i = length1, j = 0; i < sum; i = i + 1, j = j + 1) {
			finalString[i] = str3[j];
		}

		finalString[sum] = '\0';

		return (const char*)finalString;
	}
	
	const char* concat(const char *str1, char symbol) {

		int length1 = length(str1),
			sum = length1 + 1;

		char *finalString = (char*)malloc((sum + 1)*sizeof(char));

		for (int i = 0; i < length1; i++) {
			finalString[i] = str1[i];
		}

		finalString[sum-1] = symbol;	
		finalString[sum] = '\0';
		
		return (const char*)finalString;
	}

	void writeIntoFile(const char* path, mString *str) {
		FILE* file = fopen(path, "a+");
		
		if (file == NULL) {
		   std::cout << "Cannot open this file!" << std::endl;
		}
		
		fseek(file, 0, SEEK_SET);
		fwrite(str->getString(), sizeof(mString), str->getLength()+1, file);
		fclose(file);
	}
	
	void readFromFile(const char* path, char* buffer) {
		FILE* file = fopen(path, "r");
		
		if (file == NULL) {
		   std::cout << "Cannot open this file!" << std::endl;
		}
		
		fseek(file, 0, SEEK_END); 			//ставим указатель в конец файла
		unsigned int length = ftell(file); 	//возвращаем позицию указателя
		fseek(file, 0, SEEK_SET);
		buffer[length] = '\0';
		fread((void*)buffer, sizeof(char), length+1, file);
		buffer[length] = '\0';
	}
	
	int fileLength(const char* path) {
		FILE *file = fopen(path, "r");
		
		if (file == NULL) {
		   std::cout << "Cannot open this file!" << std::endl;
		}
		
		fseek(file, 0, SEEK_END);
		unsigned int length = ftell(file);
		return length;
	}

//for 3 part of 4 ex	
	int returnNumber(int num, std::stringstream &backBuffer, int cur, int last) {
		int nnum = -1;
		if (num != 32) {
			num -= 48;
		   	backBuffer << num;
		   	if (cur == last) {
		   		backBuffer >> nnum;
		   	   	return nnum;
			}
		   	return -1;	
		} else {
			backBuffer >> nnum;
			return nnum;
		}
		return -1;
	}
	
	int readFilePart(const char* path, int* number, int partition, int &position) {
		FILE* file = fopen(path, "a+");
		int file_length = vez::fileLength(path);
		fseek(file, position, SEEK_SET);
		
		int pos = ftell(file);
		fseek(file, 0, SEEK_END);
		if (pos == ftell(file)) {
			return -1;
		}
		
		fseek(file, position, SEEK_SET);
		
		if (!file) {
			std::cout << "Cant open the file!" << std::endl;
			return -1;
		}
		
		for (int i = 0; i < 5; i++) {
			number[i] = 0;
		}
		
		int num = 0, res = 0, last = file_length - 1, index = 0;
		std::stringstream ss;
		
		for (int i = 0; i < file_length; i++) {
			num = fgetc(file);
			res = returnNumber(num, ss, i, last);
			ss.clear();
			if (res != -1) {
				number[index] = res;
				index++;
				if (index >= partition) {
					position = ftell(file);
					return 1;
				}
			} 
		}
		
		return 1;
	}
	
	bool writeFile(const char* path, int numberOf) {
		srand(time(NULL));
		FILE* file = fopen(path, "a+");
		
		if (!file) {
			std::cout << "Cant open the file!" << std::endl;
			return false;
		}
		
		int randNumber = 0;
		std::string string;
		
		for (int i = 0; i < numberOf; i++) {
			randNumber = rand() % 100 + 1;
			
			std::stringstream ss;
			ss << randNumber;
			string = ss.str();
			const char* str = string.c_str();
			
			int leng = vez::length(str);
			fwrite(str, sizeof(char), leng, file);
			
			const char* str2 = " ";
			int leng2 = vez::length(str2);
			fwrite(str2, sizeof(char), leng2, file);
			
			ss.clear();
			string = "";
			randNumber = 0;
		}
		
	}
}

