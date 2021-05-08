#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <cstring>
#include "StringClass.h"

MyString::MyString() {
	str = nullptr;
	size = 0;
}

MyString::MyString(const char* _str, size_t _size) {
    if (_size == 0) {

        _size = strlen(_str);
    }
    size = _size;
    str = new char[size+1];
    for (size_t i = 0; i < size; i++) {
        str[i] = _str[i];
    }
    str[size] = '\0';
}

MyString::MyString(const MyString& other) {
    copy(other);
}

MyString::~MyString() {
    destroy();
}


void MyString::destroy() {
    delete[] str;
    str = nullptr;
}

void MyString::copy(const MyString& other) {

    if (this->str != nullptr) {
        destroy();
    }
    str = new char[other.size];
    
    strcpy(this->str, other.str);
    size = other.size;
    
}

void MyString::resize(const size_t _size) {
    if (_size < size) {
        
        return;
    }
    while (_size >= size) {
        size*=2;
    }
    char* buffer = new char[size+1];
    for (size_t i = 1; i < size; i++) {
        buffer[i] = str[i];
    }
    delete[] str;
    str = buffer;
}

void MyString::my_concat(const MyString& other) {
    resize(strlen(str) + strlen(other.str));
    strcat(this->str, other.str);
}

void MyString::push_back(const char element) {//adding element at the end of str
    char* buffer = new char[size + 1];
    for (size_t i = 0; i < size; i++) {
        buffer[i] = str[i];
    }
    destroy();
    str = new char[size + 1];
    buffer[size] = element;
    size++;
    str = buffer;
}

size_t MyString::get_lenght()const {
    return this->size;
}

const bool MyString:: is_empty()const {
    return size == 0;
}


char& MyString::operator [](const size_t index) {
    return this->str[index];

}

const char& MyString::operator [](const size_t index)const {
    return this->str[index];

}

MyString& MyString::operator =(const MyString& other) {
    if (this != &other) {
        destroy();
        str = new char[other.size];
        size = other.size;
        for (size_t i = 0; i < size; i++) {
            str[i] = other.str[i];
        }
    }
    return *this;
}

MyString& MyString::operator +(const MyString& other) {
    my_concat(other);
    return *this ;
}

bool MyString::operator ==(const MyString& other) {
    return !strcmp(this->str, other.str);
}


