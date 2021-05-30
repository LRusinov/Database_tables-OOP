#include "Column.h"

Column::Column() {
	column_type = type::Unknown;
	number_of_rows = 0;
	rows = nullptr;
}
Column::Column(Column& other) {

	this->column_type = other.column_type;
	this->number_of_rows = other.number_of_rows;
	this->rows = other.rows;
}


void Column::set_row(const size_t index, const std::string& new_row_name) {
	rows[index] = new_row_name;
}

std::string Column::get_row(const size_t n)const {
	return rows[n];
}

void Column::set_number_of_rows(const size_t n) {
	number_of_rows = n;
}

size_t Column::get_number_of_rows()const {
	return this->number_of_rows;
}

void Column::new_row(const std::string& new_row) {
	number_of_rows++;
	if (number_of_rows == 1) {
		delete[] rows;
		rows = new std::string[number_of_rows];
		rows[number_of_rows - 1] = new_row;
	}
	else {
		std::string* buff = new std::string[number_of_rows];

		for (size_t i = 0; i < number_of_rows - 1; i++) {
			buff[i].resize(20);
			buff[i] = rows[i];
		}

		delete[] rows;
		rows = new std::string[number_of_rows];
		for (size_t i = 0; i < number_of_rows - 1; i++) {
			rows[i].resize(20);
			rows[i] = buff[i];
		}
		rows[number_of_rows - 1] = new_row;

		delete[] buff;
	}

}

void Column::print_row() {
	for (size_t i = 0; i < number_of_rows; i++) {
		std::cout << this->rows[i] << " ";
	}
	std::cout << std::endl;
}

void Column::delete_row(const size_t n) {
	number_of_rows--;
	std::string* buff = new std::string[number_of_rows];
	for (size_t i = n; i < number_of_rows; i++) {
		rows[i] = rows[i + 1];
	}
	for (size_t i = 0; i < number_of_rows; i++) {
		buff[i] = rows[i];
	}
	delete[] rows;
	rows = new std::string[number_of_rows];
	for (size_t i = 0; i < number_of_rows; i++) {
		rows[i] = buff[i];
	}
	delete[] buff;
}


void Column::set_columtype(const std::string& _column_type) {
	if (_column_type == "String") {
		column_type = type::String;
	}
	else if (_column_type == "Double") {
		column_type = type::Double;
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
	else if (!(_rows[0][0] >= '1' && _rows[0][0] <='9')) {
		std::cout << "Unknown columntype!";
		return type::Unknown;
	}
	else {
		bool is_there_a_point = false;
		size_t len = _rows[0].length();
		for (size_t i = 0; i < len + 1; i++) {
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


double Column::string_to_double(const std::string& str) {
	bool sig = false, sig_minus = false;
	double result = 0;
	size_t temp = 0, start_index = 0, length = str.length();
	if (str[0] == '+' || str[0] == '-') {
		sig = true;
		start_index = 1;
		if (str[0] == '-') {
			sig_minus = true;
		}
	}



	for (size_t i = start_index; i < length; i++) {
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '.') {
			length = i;
			break;
		}
	}
	int s = length;
	if (sig) {

		s--;
	}

	for (size_t i = start_index; i < length; i++) {

		if (str[i] == '.') {
			temp = i + 1;
			s -= i;
			break;
		}
		result += (double(str[i]) - 48) * pow(10, s);

		s--;
	}
	if (!sig) {
		s--;
	}
	result = result / pow(10, (length - temp + 2));
	for (size_t i = temp; i < length; i++) {

		result += (double(str[i]) - 48) * pow(10, s);
		s--;
	}
	if (sig_minus) {
		return result * -1;
	}
	else {
		return result;
	}
}

int Column::string_to_int(const std::string& str) {
	bool sig = false, sig_minus = false;
	int result = 0;
	size_t temp = 0, start_index = 0, length = str.length();

	if (str[0] == '+' || str[0] == '-') {
		sig = true;
		start_index = 1;
		if (str[0] == '-') {
			sig_minus = true;
		}
	}



	for (size_t i = start_index; i < length; i++) {
		if (!(str[i] >= '0' && str[i] <= '9')) {
			length = i;
			break;
		}
	}
	int s = length;
	if (sig) {

		s--;
	}
	s--;
	for (size_t i = start_index; i < length; i++) {
		result += (str[i] - 48) * pow(10, s);

		s--;
	}
	if (sig_minus) {
		return result * -1;
	}
	else {
		return result;
	}
}
