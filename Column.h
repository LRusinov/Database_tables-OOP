#include "StringClass.h"
enum class type{Integer,Double,String,Null};
class Column {
private:
	type column_type;
	size_t number_of_rows;
	MyString* rows;
public:
	Column() {
		column_type = type::Null;
		number_of_rows = 0;
		rows=nullptr;
	}
	Column(Column& other) {

			this->column_type = other.column_type;
			this->number_of_rows = other.number_of_rows;
			this->rows = other.rows;
	}
	~Column() {
		delete[] rows;
	}


	void set_columtype(type _column_type) {
		column_type = _column_type;
	}
	type get_columtype() {
		return this->column_type;
	}
	type type_check(MyString* _rows) {
		if (_rows[0][0] == '"') {
			return type::String;
		}
		else {
			if (_rows[0].get_lenght() == 0) {
				return type::Null;
			}
			bool is_there_a_point = false;

			for (size_t i = 0; i < _rows[0].get_lenght()+1; i++) {
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
	void Read_from_file();

	

};