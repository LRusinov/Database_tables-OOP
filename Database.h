#include "Table.h"
#include <vector>
class Database{
private:
	Table* all_tables;
	std::string* names_of_files;
	size_t number_of_files;
	size_t number_of_tables;
public:
	Database();
	Database(Database& other);
	
	void import(const std::string& file);///
	void showtables();///
	void describe(const std::string& table_name);///
	void print(const std::string& table_name);///
	void select(const size_t column_n,const std::string& value,const std::string& table_name);///
	void addcolumn(const std::string& table_name, const std::string& column_name,const std::string& column_type);///
	void remove(const std::string& table_name, const size_t column_n,const std::string& value);///
	void rename(const std::string& old_name,const std::string& new_name);///
	void count(const std::string& table_name, const size_t column_n,const std::string& value);///
	void export_table(const std::string& table_name,const std::string& file_name);///
	void update(const std::string& table_name, const size_t column_n,const std::string& value, const size_t target_column_n, const std::string& target_value);///
	void aggregate(const std::string& table_name, const size_t column_n,const std::string& value, const size_t target_column_n, const std::string& operation);//!!!!!
	
	void print_menu_options() ;
	void menu();
	bool if_table_is_opened(const std::string& table_name);

	std::string remove_spaces(std::string str);// & ???
	int find_table(const std::string& table_name);

	void insert(const std::string& table_name, const std::string* arr, const size_t size_of_arr, const size_t index);
	void innerjoin(const std::string& table_1, const size_t column_num_1, const std::string& table_2, const size_t column_num_2);

};
