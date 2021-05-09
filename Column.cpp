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


void Column::set_columtype(std::string _column_type) {
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
type Column::get_columtype() {
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
std::string Column::get_row(size_t n) {
	return rows[n];
}
void Column::set_row(std::string new_row) {
	std::string* buff = new std::string[number_of_rows+1];
	for (size_t i = 0; i < number_of_rows; i++) {
		buff[i] = rows[i];		
	}
	number_of_rows++;
	delete[] rows;
	rows = new std::string[number_of_rows];
	rows = buff;
	rows[number_of_rows-1] = new_row;
}
