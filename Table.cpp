#include"Table.h"
#include<fstream>
void Table::Read_from_file(std::ifstream&  myfile) {
    size_t counter = 0,column_counter=0;
    std::string text;   
    while (getline(myfile, text) && text != "") {
        counter++;
        if (counter == 1) {
            for (size_t i = 0; i < text.length(); i++) {
                if (text[i] == ',') {
                    number_of_colums++;
                }
            }
            number_of_colums++;
            delete[] columns;
            columns = new Column[number_of_colums];
            size_t index = 0;
            while (index < text.length()) {

                if (text[index] == 'S') {
                    columns[column_counter].set_columtype("String");
                    index += 7;
                    column_counter++;
                }
                else if (text[index] == 'D') {
                    
                    columns[column_counter].set_columtype("Double");
                    index += 7;
                    column_counter++;
                }
                else if (text[index] == 'I') {
                    columns[column_counter].set_columtype("Integer");
                    index += 7;
                    column_counter++;
                }
                else if (text[index] == 'N') {
                    columns[column_counter].set_columtype("Null");
                    index += 5;
                    column_counter++;
                }
                else {
                    std::cout << text[index];
                    std::cout << "Unknown type";
                    break;
                }
            }
            counter++;
        }
        else if (counter == 2) {
            name = text;
            counter++;
        }
        else if(text[0]=='|'){
            

            column_counter = 0;
            size_t index=1,i=0;
            std::string buff;
            buff.resize(text.length()+1);
            while (index < text.length()-1&& column_counter<number_of_colums) {
                
                while (text[index] != '|') {
          
                    buff[i] = text[index];
                
                    i++;
                    index++;
                }
                
                columns[column_counter].set_row(buff);
                
                
                column_counter++;
                i = 0;
                index++;
            }

        }
    }
myfile.close();
}
void Table::print() {
    size_t counter=0;
    
    for (size_t i = 0; i < number_of_colums * 19;i++) {
        std::cout << "=";
    }
    std::cout << std::endl;
    while (counter < columns[0].get_number_of_rows()) {
        std::cout << "|";
        for (size_t i = 0; i < number_of_colums; i++) {
            std::cout << columns[i].get_row(counter);
            if (columns[i].get_row(counter).length() < 20) {
                for (size_t g = 0; g < 20 - columns[i].get_row(counter).length(); g++) {
                    std::cout << " ";
                }
            }
            std::cout << "|";
        }
        std::cout << std::endl;
        for (size_t i = 0; i < number_of_colums * 19; i++) {
            std::cout << "=";
        }
        std::cout << std::endl;
        counter++;
    }

}
template<typename T>
T Table::add(T* arr, const size_t size_of_arr, const T element_to_add) {
    T* buff = new T[size_of_arr];
    for (size_t i = 0; i < number_of_tables - 1; i++) {
        buff[i] = arr[i];
    }
    delete[] arr;
    arr = new T[size_of_arr];
    for (size_t i = 0; i < size_of_arr - 1; i++) {
        arr[i] = buff[i];
    }
    delete[] buff;
    arr[size_of_arr - 1] = element_to_add;
}
std::string Table::get_name()const{
    return name;
}
void Table::show_columnstypes(){
    for (size_t i = 0; i < number_of_colums; i++) {
        switch (columns[i].get_columtype()) {
        case type::Double: std::cout << "Double"<<std::endl; break;
        case type::Integer: std::cout << "Integer" << std::endl; break;
        case type::String: std::cout << "String" << std::endl; break;
        case type::Null: std::cout << "Null" << std::endl; break;
        }
    }

}
void Table::search_row(const size_t n, const std::string value) {
    for (size_t i = 0; i < columns[n-1].get_number_of_rows(); i++) {
        if (columns[n - 1].get_row(i) == value) {//////
        }
    }
}
