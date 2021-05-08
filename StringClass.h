#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<iostream>
#include <string>
#include <cstring>
class MyString {
private:
    char* str;
    size_t size;
    void copy(const MyString& other);
    void destroy();

public:

    //Constructors
    MyString();
    MyString(const char* _str,size_t _size = 0);
    MyString(const MyString& other);
    ~MyString();

    // Methods
    void resize(const size_t _size);
    void my_concat(const MyString& other);
    void push_back(const char element);
    size_t get_lenght()const;
    const bool is_empty()const;

    // Operators
    char& operator [](const size_t index);
    const char& operator [](const size_t index) const;
    MyString& operator =(const MyString& other);
    MyString& operator +(const MyString& other);
    bool operator ==(const MyString&other); 
    friend std::ostream& operator <<(std::ostream& os, MyString& output) {
        for (size_t i = 0; i < output.size; i++) {
            os << output.str[i];
        }
        return os;
    }
    friend std::istream& operator >>(std::istream& in, MyString& input) {
        std::string s;
            getline(in,s);
            input.destroy();
            input.str = new char[s.length()];
            input.size = s.length();
            std::cout << s.length();

            for (size_t i = 0; i < s.length(); i++) {
                input.str[i] = s[i];
            }
        return in;
    }
};
