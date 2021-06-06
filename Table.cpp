#include"Table.h"
#include<fstream>

Table::Table() {
    name = "";
    number_of_columns = 0;
    columns = nullptr;
}

void Table::set_name(const std::string& new_name) {
    this->name = new_name;
}

std::string Table::get_name()const{
    return name;
}

void Table::set_num_of_columns(const size_t& n) {
    number_of_columns = n;
}

size_t Table::get_num_of_columns()const {
    return number_of_columns;
}

void Table::set_column(const size_t& n, const Column& column) {
    columns[n] = column;
}

Column& Table::get_column(const size_t& n)const {
    return columns[n];
}

void Table::new_columns(const size_t& size) {
    columns = new Column[size];
}

Column* Table::get_columns()const {
    return this->columns;
}

//Изтрива всички колони в таблицата.
void Table::destroy_columns() {
    delete[] columns;
}

//Принтира типовете на колоните.
void Table::show_columnstypes(){
    for (size_t i = 0; i < number_of_columns; i++) {
        std::cout << std::endl;
        switch (columns[i].get_columtype()) {
        case type::Double: std::cout << i + 1 << ". " << "Double"; break;
        case type::Integer: std::cout << i + 1 << ". " << "Integer"; break;
        case type::String: std::cout << i + 1 << ". " << "String"; break;
        case type::Unknown: std::cout << i + 1 << ". " << "Unknown"; break;
        }
    }
}

//Търси таблица по подаден масив от таблици.
bool Table::search_table(const std::string& name, const Table* tables, const size_t& num_of_tables) {
    for (size_t i = 0; i < num_of_tables; i++) {
        if (tables[i].get_name() == name) {
            *this = tables[i];
            break;
        }
    }
    if (get_name() == "") {
        std::cout << "There is no table with this name in the database!" << std::endl;
        return false;
    }
    else {
        return true;
    }
}

//Принтира таблица в диалогов режим за разглеждане по страници.
void Table::print_with_pages() {
    std::string input;
    size_t counter = 0, num_of_r = columns[0].get_number_of_rows(), printed_columns=0, limit=4, curr_page=1, all_pages;
    std::cout << name << std::endl;
    if (number_of_columns % 4 == 0) {
        all_pages = number_of_columns / 4;
    }
    else {
        all_pages = number_of_columns / 4 + 1;
    }
        while (input!="e") {

            if (input == "p" && printed_columns == 0) {
                std::cout << "There is no previous page.";
            }
            else if (input == "n" && printed_columns + limit == number_of_columns) {
                std::cout << "There is no next page.";
            }
            else {
                if (input == "n") {
                    curr_page++;
                    printed_columns += limit;
                }
                if (input == "p") {
                    curr_page--;
                    printed_columns -= 4;
                }
                if (curr_page < number_of_columns / 5 || number_of_columns - printed_columns > 4) {
                    limit = 4;

                }
                else {
                    limit = number_of_columns - printed_columns;
                }
                for (size_t i = 0; i < limit * 21 + 1; i++) {
                    std::cout << "=";
                }
                std::cout << std::endl;

                counter = 0;
                while (counter < num_of_r) {
                    std::cout << "|";
                    for (size_t i = printed_columns; i < limit + printed_columns; i++) {
                        std::cout << columns[i].get_row(counter);
                        if (columns[i].get_row(counter).length() < 20) {
                            size_t len = columns[i].get_row(counter).length();
                            for (size_t g = 0; g < 20 - len; g++) {
                                std::cout << " ";
                            }
                        }
                        std::cout << "|";
                    }
                    std::cout << std::endl;
                    for (size_t i = 0; i < limit * 21 + 1; i++) {
                        std::cout << "=";
                    }
                    std::cout << std::endl;

                    counter++;
                }
            }
            std::cout << "Page "<< curr_page<<"/"<<all_pages<<std::endl;
            std::cout << "n-Next page  p-Previous page  e-Exit";
            std::cin >> input;
        }
}

//Принтира таблицата.
void Table::print() {
    size_t counter = 0, num_of_r = columns[0].get_number_of_rows(), printed_columns = 0, limit, curr_page = 1;
    std::cout << name << std::endl;
    while (printed_columns != number_of_columns) {
        if (number_of_columns - printed_columns > 4) {
            limit = 4;
        }
        else {
            limit = number_of_columns - printed_columns;
        }
        for (size_t i = 0; i < limit * 21 + 1; i++) {
            std::cout << "=";
        }
        std::cout << std::endl;

        counter = 0;
        while (counter < num_of_r) {
            std::cout << "|";
            for (size_t i = printed_columns; i < limit + printed_columns; i++) {
                std::cout << columns[i].get_row(counter);
                if (columns[i].get_row(counter).length() < 20) {
                    size_t len = columns[i].get_row(counter).length();
                    for (size_t g = 0; g < 20 - len; g++) {
                        std::cout << " ";
                    }
                }
                std::cout << "|";
            }
            std::cout << std::endl;
            for (size_t i = 0; i < limit * 21 + 1; i++) {
                std::cout << "=";
            }
            std::cout << std::endl;
            counter++;
        }
        printed_columns += limit;
    }
}

//Чете таблица от файл.
void Table::Read_from_file(const std::string& file_name) {
    std::ifstream myfile(file_name);
    size_t counter = 0, column_counter = 0;
    std::string text;
    while (getline(myfile, text) && text != "") {
        counter++;
        if (counter == 1) {
            size_t index = 0, len = text.length();
            for (size_t i = 0; i < len; i++) {
                if (text[i] == ',') {
                    number_of_columns++;
                }
            }
            number_of_columns++;
            delete[] columns;
            columns = new Column[number_of_columns];
            while (index < len) {
                if (text.compare(index, 6, "String") == 0) {
                    columns[column_counter].set_columtype("String");
                    index += 7;
                    column_counter++;
                }
                else if (text.compare(index, 6, "Double") == 0) {

                    columns[column_counter].set_columtype("Double");
                    index += 7;
                    column_counter++;
                }
                else if (text.compare(index, 7, "Integer") == 0) {
                    columns[column_counter].set_columtype("Integer");
                    index += 8;
                    column_counter++;
                }
                else {
                    std::cout << "Unknown type" << std::endl;
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
        else if (text[0] == '|') {
            size_t length = text.length();
            column_counter = 0;
            size_t index = 1, i = 0;
            std::string buff;
            buff.resize(20);
            while (index < length - 1 && column_counter < number_of_columns) {

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

//Пише таблица във файл.
void Table::export_to_file(const std::string& file_name) {
    size_t num_of_c = get_num_of_columns();
    size_t num_of_r = get_column(0).get_number_of_rows();
    std::ofstream myfile;
    myfile.open(file_name, std::ios::out);
    for (size_t i = 0; i < num_of_c; i++) {

        switch (get_column(i).get_columtype()) {
        case type::Double: myfile << "Double"; break;
        case type::Integer: myfile << "Integer"; break;
        case type::String: myfile << "String"; break;
        }
        if (i + 1 < num_of_c) {
            myfile << ",";
        }
    }
    myfile << std::endl;
    myfile << get_name() << std::endl;
    size_t counter = 0;
    for (size_t i = 0; i < num_of_c * 21; i++) {
        myfile << "=";
    }
    myfile << std::endl;
    while (counter < num_of_r) {
        myfile << "|";
        for (size_t i = 0; i < num_of_c; i++) {
            myfile << get_column(i).get_row(counter);
            if (get_column(i).get_row(counter).length() < 20) {
                size_t len = get_column(i).get_row(counter).length();
                for (size_t g = 0; g < 20 - len; g++) {
                    myfile << " ";
                }
            }
            myfile << "|";
        }
        myfile << std::endl;
        for (size_t i = 0; i < num_of_c * 21; i++) {
            myfile << "=";
        }
        myfile << std::endl;
        counter++;
    }
    myfile.close();
}

Table& Table::operator=(const Table& other) {
    this->name = other.name;
    this->columns = other.columns;
    this->number_of_columns = other.number_of_columns;
    return *this;
}
