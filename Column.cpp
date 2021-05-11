#include "Column.h"
Column::Column() {
	column_type = type::Null;
	number_of_rows = 0;
	rows = nullptr;
}
Column::Column(Column& other) {

	this->column_type = other.column_type;
	this->number_of_rows = other.number_of_rows;
	this->rows = other.rows;
}
Column::~Column() {
	delete[] rows;
}
size_t Column::get_number_of_rows()const {
	return number_of_rows;
}

void Column::set_columtype(const std::string _column_type) {
	if (_column_type == "String") {
		column_type = type::String;
	}
	else if (_column_type == "Double") {
		column_type = type::Double;
	}
	else if (_column_type == "Null") {
		column_type = type::Null;
	}
	else if (_column_type == "Integer") {
		column_type = type::Integer;
	}
	else {
		std::cout << "Unknown column type!";
	}
}
type Column::get_columtype()const {
	return this->column_type;
}
type Column::type_check(std::string* _rows) {
	if (_rows[0][0] == '"') {
		return type::String;
	}
	else if (_rows[0][0] < '1' && _rows[0][0] > '0') {
		std::cout << "Unknown columntype!";
	}
	else {
		if (_rows[0].length() == 0) {
			return type::Null;
		}
		bool is_there_a_point = false;
		for (size_t i = 0; i < _rows[0].length() + 1; i++) {
			if (_rows[0][i] == '.') {
				is_there_a_point = true;
				break;
			}
		}
		if (is_there_a_point) {
			return type::Double;
		}
		else {
			return type::Integer;
		}
	}
}
std::string Column::get_row(const size_t n)const {
	return rows[n];
}
void Column::set_row(const std::string new_row) {
	number_of_rows++;
	if (number_of_rows == 1) {
		rows = new std::string[number_of_rows];
		rows[number_of_rows-1] = new_row;
	}
	else {
		std::string* buff = new std::string[number_of_rows];

		for (size_t i = 0; i < number_of_rows-1; i++) {
			buff[i].resize(20);
			buff[i] = rows[i];
		}
		
		delete[] rows;
		rows = new std::string[number_of_rows ];
		for (size_t i = 0; i < number_of_rows-1; i++) {
			rows[i].resize(20);
			rows[i] = buff[i];
		}
		rows[number_of_rows-1] = new_row;

		delete[] buff;
	}

}
void Column::pr() {
	for (int i = 0; i < number_of_rows; i++) {
		std::cout << rows[i];
	}
	std::cout << std::endl;
}
