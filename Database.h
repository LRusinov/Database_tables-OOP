#include "Table.h"
#include <vector>
class Database{
private:
	Table* all_tables;
	std::string* names_of_files;//????
	size_t number_of_files;
	size_t number_of_tables;
public:
	Database();
	Database(Database& other);
	std::string remove_spaces(std::string str);// & ???
	int find_table(const std::string& table_name);
	void import(const std::string& file);///
	void showtables();///
	void describe(const std::string& table_name);///
	void print(const std::string& table_name);///
	void select(const size_t column_n, std::string value,const std::string& table_name);///
	void addcolumn(const std::string& table_name,const std::string& column_type);///
	void remove(const std::string& table_name, const size_t column_n,const std::string& value);///
	void rename(const std::string& old_name,const std::string& new_name);///
	void count(const std::string& table_name, const size_t column_n,const std::string& value);///
	void export_table(const std::string& table_name,const std::string& file_name);///
	void update(const std::string& table_name, const size_t column_n,const std::string& value, const size_t target_column_n, const std::string& target_value);///
	void aggregate(const std::string& table_name, const size_t column_n,const std::string& value, const size_t target_column_n, const std::string& operation);//!!!!!
	void menu_options_out();
	void menu();
	//insert <table name> <column 1> … <column n>
	//innerjoin <table 1> <column n1> <table 2> <column n2>



};
