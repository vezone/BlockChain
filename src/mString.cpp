#include <cstring>
#include <sstream>

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
		fseek(file, 0, SEEK_END);
		
		if (file == NULL) {
		   std::cout << "Cannot open this file!" << std::endl;
		}
		
		fseek(file, 0, SEEK_SET);
		fwrite(str->getString(), sizeof(char), str->getLength(), file);
		fclose(file);
	}
	
	char* readFromFile(const char* path) {
		FILE* file = fopen(path, "a+");
		fseek(file, 0, SEEK_END); 			//ставим указатель в конец файла
		unsigned int length = ftell(file); 	//возвращаем позицию указателя
		char* buffer = new char[length+1];
		fseek(file, 0, SEEK_SET);
		fread((void*)buffer, sizeof(char)*8, length, file);
		buffer[length] = '\0';
		return buffer;
	}
	
	int fileLength(const char* path) {
		FILE *file = fopen(path, "r");
		fseek(file, 0, SEEK_END);
		unsigned int length = ftell(file);
		return length;
	}
}

