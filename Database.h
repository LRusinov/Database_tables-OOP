#include "Table.h"

class Database{
private:
	Table* all_tables;
	std::string* names_of_files;
	size_t number_of_files;
	size_t number_of_tables;
public:

	//Constructors
	Database();
	Database(Database& other);
	
	//Get functions
	size_t get_num_of_files()const;
	size_t get_num_of_tables()const;
	Table& get_table(const size_t index);

	//Main functions
	void import(const std::string& file);
	void showtables();
	void describe(const std::string& table_name);
	void print(const std::string& table_name);
	void select(size_t column_n,const std::string& value,const std::string& table_name);
	void addcolumn(const std::string& table_name, const std::string& column_name,const std::string& column_type);
	void remove(const std::string& table_name, size_t column_n,const std::string& value);
	void rename(const std::string& old_name,const std::string& new_name);
	void insert(const std::string& table_name, const std::string* arr, const size_t& size_of_arr, const size_t& index);
	void innerjoin(const std::string& table_1, size_t column_num_1, const std::string& table_2, size_t column_num_2);
	void count(const std::string& table_name, size_t column_n,const std::string& value);
	void export_table(const std::string& table_name,const std::string& file_name,const bool& flag = false);
	void update(const std::string& table_name, size_t column_n,const std::string& value, size_t target_column_n, const std::string& target_value);
	void aggregate(const std::string& table_name, size_t column_n,const std::string& value, size_t target_column_n, const std::string& operation);
	
	//Helper functions
	void print_menu_options() ;
	void menu();
	bool if_table_is_opened(const std::string& table_name);

	std::string remove_spaces(std::string str);
	int find_table(const std::string& table_name);
	std::string enum_to_string(const type& type_of_c);
	void value_input_validation(std::string& input, const size_t& size);
	void column_input_validation(size_t& input, const size_t& size);
	void columntype_input_validation(std::string& input);
};
