#include "Table.h"

class Database{
private:
	Table* all_tables;
	std::string* names_of_files;
	size_t number_of_files;
	size_t number_of_tables;
public:
	Database() {
		all_tables = nullptr;
		names_of_files = nullptr;
		number_of_files = 0;
		number_of_tables = 0;
	}
	void import(const std::string file);
	void showtables();
	void describe(const std::string table_name);
	void print(const std::string table_name);
	void select(const size_t column_n,const std::string value,const std::string table_name);
	void addcolumn(std::string table_name, std::string column_name, std::string column_type);
	void remove(std::string table_name, std::string column_name, std::string value);
	void rename(std::string old_name, std::string new_name);
	void count(std::string table_name, std::string column_name, std::string value);
	void describe(std::string table_name);
	
	//void export(std::string table_name, std::string file_name);

};
