#include "StringClass.h"
enum class type{Integer,Double,String,Null};
class Column {
private:
	type column_type;
	size_t number_of_rows;
	std::string* rows;
public:
	Column();
	Column(Column& other);
	~Column();

	size_t get_number_of_rows();
	void set_columtype(std::string _column_type);
	type get_columtype();
	type type_check(std::string* _rows);
	void set_row(std::string new_row);
	std::string get_row(size_t n);
	void pr();

	

};
