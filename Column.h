#include<iostream>
#include<string>

enum class type{Integer,Double,String,Unknown};

class Column {
private:
	type column_type;
	size_t number_of_rows;
	std::string* rows;
public:
	//Constructors
	Column();
	Column(Column& other);

	void set_row(const size_t& index, const std::string& new_row_name);
	std::string get_row(const size_t& n)const;
	void set_number_of_rows(const size_t& n);
	size_t get_number_of_rows()const;
	void new_row(const std::string& new_row);
	void delete_row(const size_t& n);

	void set_columtype(const std::string& _column_type);
	type get_columtype()const;

	//Helper functions
	double string_to_double(const std::string& str);
	int string_to_int(const std::string& str);
};
