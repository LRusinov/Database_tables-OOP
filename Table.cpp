#include"Table.h"
#include<fstream>
void Table::Read_from_file() {
    size_t counter = 0,column_counter=0;
    std::string text;
    std::ifstream  myfile("example.txt");   
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
            buff.resize(text.length());
            while (index < text.length() - 1) {
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
    for (size_t i = 0; i < number_of_colums * 21 + 1;i++) {
        std::cout << "=";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < number_of_colums ; i++) {
        std::cout << columns[i].get_row(counter);
        if (columns[i].get_row(counter).length() < 20) {
            for (size_t i = 0; i < 20 - columns[i].get_row(counter).length(); i++) {
                std::cout << " ";
            }
        }
        std::cout << "|"<<std::endl;
        counter++;
        for (size_t i = 0; i < number_of_colums * 21 ; i++) {
            std::cout << "=";
        }
        std::cout << "|" << std::endl;
    }

}
