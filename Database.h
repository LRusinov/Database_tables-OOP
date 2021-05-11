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
	void addcolumn(std::string table_name, std::string column_type);
	void remove(const std::string table_name, const size_t column_n,const std::string value);
	void rename(std::string old_name, std::string new_name);
	size_t count(const std::string table_name, const size_t column_n, const std::string value);
	void export_table(const std::string table_name,const std::string file_name);
	void update(const std::string table_name, const size_t column_n, const std::string value, const size_t target_column_n, const std::string target_value);

	//insert <table name> <column 1> … <column n>
	//innerjoin <table 1> <column n1> <table 2> <column n2>
	//aggregate <table name> <search column n> <search value> <target column n> <operation>



};
