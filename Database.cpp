#include "Database.h"
#include<fstream>
void Database::showtables() {
	for (size_t i = 0; i < number_of_tables; i++) {
		all_tables[i].print();
	}
}
void Database::import(const std::string filename) {
	Table new_table;
	std::ifstream file(filename);
	new_table.Read_from_file(file);
	number_of_tables++;
	number_of_files++;
	new_table.add<Table>(all_tables, number_of_tables, new_table);
	new_table.add<std::string>(names_of_files, number_of_files, filename);
}
void Database::describe(const std::string table_name) {
	Table searched_table;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == table_name) {
			searched_table = all_tables[i];
			break;
		}

	}
	searched_table.show_columnstypes();

}
void Database::print(const std::string table_name) {
	Table searched_table;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == table_name) {
			searched_table = all_tables[i];
			break;
		}
		searched_table.print();

	}
}
void Database::select(const size_t column_n,const std::string value,const std::string table_name) {
	Table searched_table;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == table_name) {
			searched_table = all_tables[i];
			break;
		}


	}
}
