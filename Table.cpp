#include"Table.h"
#include<fstream>
Table::Table() {
    name = "";
    number_of_columns = 0;
    columns = nullptr;
}
/*Table::~Table() {
    delete[] columns;
}*/
void Table::Read_from_file(const std::string  file_name) {
    std::ifstream myfile(file_name);
    size_t counter = 0,column_counter=0;
    std::string text;   
    while (getline(myfile, text) && text != "") {
        counter++;
        if (counter == 1) {
            for (size_t i = 0; i < text.length(); i++) {
                if (text[i] == ',') {
                    number_of_columns++;
                }
            }
            number_of_columns++;
            delete[] columns;
            columns = new Column[number_of_columns];
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
        if (counter == 2) {
            getline(myfile, text);
            name = text;
            
            counter++;
        }
        else if(text[0]=='|'){
            
            column_counter = 0;
            size_t index=1,i=0;
            std::string buff;
            buff.resize(20);
            while (index < text.length()-1&& column_counter<number_of_columns) {
                
                while (text[index] != '|') {
          
                    buff[i] = text[index];
                
                    i++;
                    index++;
                }
                
                columns[column_counter].new_row(buff);           
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
    std::cout << name << std::endl;
    for (size_t i = 0; i < number_of_columns * 19;i++) {
        std::cout << "=";
    }
    std::cout << std::endl;
    while (counter < columns[0].get_number_of_rows()) {
        std::cout << "|";
        for (size_t i = 0; i < number_of_columns; i++) {
            std::cout << columns[i].get_row(counter);
            if (columns[i].get_row(counter).length() < 20) {
                for (size_t g = 0; g < 18 - columns[i].get_row(counter).length(); g++) {
                    std::cout << columns[i].get_row(counter).length() ;
                }
            }
            std::cout << "|";
        }
        std::cout << std::endl;
        for (size_t i = 0; i < number_of_columns * 19; i++) {
            std::cout << "=";
        }
        std::cout << std::endl;
        counter++;
    }

}

std::string Table::get_name()const{
    return name;
}
void Table::show_columnstypes(){
    for (size_t i = 0; i < number_of_columns; i++) {
        switch (columns[i].get_columtype()) {
        case type::Double: std::cout <<i+1<<". " <<"Double"<<std::endl; break;
        case type::Integer: std::cout << i+1 << ". "<< "Integer" << std::endl; break;
        case type::String: std::cout << i+1 << ". " << "String" << std::endl; break;
        case type::Null: std::cout << i+1 << ". " << "Null" << std::endl; break;
        }
    }

}
void Table::search_rows(const size_t n, const std::string value) {
    for (size_t i = 0; i < columns[n-1].get_number_of_rows(); i++) {
        if (columns[n - 1].get_row(i) == value) {
            columns[n - 1].print_row();
        }
    }
}
Table& Table::search_table(const std::string name, const Table* tables, const size_t num_of_tables) {
    for (size_t i = 0; i < num_of_tables; i++) {
        if (tables[i].get_name() == name) {
            *this = tables[i];
            break;
        }
    }
    return *this;
}
Table& Table::operator=(const Table& other) {
    this->name = other.name;
    this->columns = other.columns;
    this->number_of_columns = other.number_of_columns;
    return *this;
}
Column* Table::get_columns()const {
    return this->columns;
}
Column& Table::get_column(const size_t n)const {
    return columns[n];
}
size_t Table::get_num_of_columns()const {
    return number_of_columns;
}
void Table::set_name(const std::string new_name) {
    this->name = new_name;
}
void Table::set_num_of_columns(const size_t n) {
    number_of_columns = n;
}
void Table::destroy_columns() {
    delete[] columns;
}
void Table::new_columns(const size_t size) {
    columns = new Column[size];
}
void Table::set_column(const size_t n, const Column column) {
    columns[n] = column;

}
