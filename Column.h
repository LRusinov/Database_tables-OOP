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
	
	size_t get_number_of_rows()const;
	void set_columtype(const std::string _column_type);
	type get_columtype()const;
	type type_check(std::string* _rows);
	void set_row(const std::string new_row);
	std::string get_row(const size_t n)const;
	void pr();
	void print_row();
	void delete_row(const size_t n);

	

};
