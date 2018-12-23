#include <stdio.h>
#include <string.h>
#include <uuid.h>
#include "Guid.h"

#include <iostream>

namespace ndsl {
namespace utils {

Guid::Guid(){}

int Guid::generate(){
	uuid_generate(gu);
	return 0;
}

int Guid::toString(char* str){
	char* str2 = str;
	for(int i = 0; i < 16; i++){
		sprintf(str2, "%02X", gu[i]);
		str2 += 2;
	}
	return 0;
}

int Guid::toGuid_t(char* str){
	char* str2 = str;
	short int tmp[32];
	for(int i = 0; i < 32; i++){
		if(*str2 <= '9' && *str2 >= '0') {	
		tmp[i] = *str2-48;
		}else{
			switch(*str2){
				case 'A':tmp[i] = 10;break;
				case 'B':tmp[i] = 11;break;
				case 'C':tmp[i] = 12;break;
				case 'D':tmp[i] = 13;break;
				case 'E':tmp[i] = 14;break;
				case 'F':tmp[i] = 15;break;
				case 'a':tmp[i] = 10;break;
				case 'b':tmp[i] = 11;break;
				case 'c':tmp[i] = 12;break;
				case 'd':tmp[i] = 13;break;
				case 'e':tmp[i] = 14;break;
				case 'f':tmp[i] = 15;break;
				default:return -1;
			}
		}
		str2++;
	}
	for(int i = 0; i < 16; i++){
		gu[i] = tmp[2*i] << 4 | tmp[2*i+1];
	}
	return 0;
}

bool Guid::operator==(const Guid& guid) const{
	char str1[32], str2[32];
	toString(str1);
	guid.toString(str2);
	if((strcmp(str1, str2)) == 0){
		return true;
	}else{
		return false;
	}
}

bool Guid::operator<(const Guid& guid) const{
	char str1[32], str2[32];
	toString(str1);
	guid.toString(str2);
	if((strcmp(str1, str2)) < 0){
		return true;
	}else{
		return false;
	}
}

bool Guid::operator>(const Guid& guid) const{
	char str1[32], str2[32];
	toString(str1);
	guid.toString(str2);
	if((strcmp(str1, str2)) > 0){
		return true;
	}else{
		return false;
	}
}




} // namespace utils
} // namespace ndsl
