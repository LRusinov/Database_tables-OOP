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
	searched_table.search_table(table_name, all_tables, number_of_tables);
	searched_table.search_rows(column_n, value);
}

void Database::addcolumn(std::string table_name, std::string column_type) {
	Table searched_table;
	Column new_column;
	searched_table.search_table(table_name, all_tables, number_of_tables);
	searched_table.add<Column>(searched_table.get_columns(), searched_table.get_num_of_columns(), new_column);
	searched_table.get_column(searched_table.get_num_of_columns() - 1).set_columtype(column_type);
}
void Database::remove(const std::string table_name, const size_t column_n, const std::string value) {
	Table searched_table;
	searched_table.search_table(table_name, all_tables, number_of_tables);
	for (size_t i = 0; i < searched_table.get_num_of_columns(); i++) {
		if (searched_table.get_column(column_n).get_row(i) == value) {
			searched_table.get_column(column_n).delete_row(i);
		}
	}

}
void Database::rename(std::string old_name, std::string new_name) {
	Table searched_table;
	searched_table.search_table(old_name, all_tables, number_of_tables);
	searched_table.search_table(new_name, all_tables, number_of_tables);
	if (searched_table.get_name() != new_name) {
		searched_table.set_name(new_name);
	}
	else {
		std::cout << "There is table with this name in the database!" << std::endl;
	}
}

void Database::export_table(const std::string table_name, const std::string file_name){
	Table searched_table;
	searched_table.search_table(table_name, all_tables, number_of_tables);
	std::ofstream myfile;
	myfile.open(file_name, std::ios::out);
	for (size_t i = 0; i < searched_table.get_num_of_columns(); i++) {
		switch (searched_table.get_column(i).get_columtype()) {
		case type::Double: myfile << "Double" << std::endl;   break;
		case type::Integer: myfile << "Integer" << std::endl;   break;
		case type::String: myfile << "String" << std::endl;   break;
		case type::Null: myfile << "Null" << std::endl;   break;
		}
		myfile << ",";
	}
	myfile << std::endl;
	myfile << searched_table.get_name()<<std::endl;
	size_t counter = 0;
	for (size_t i = 0; i < searched_table.get_num_of_columns() * 19; i++) {
		myfile << "=";
	}
	myfile << std::endl;
	while (counter < searched_table.get_column(0).get_number_of_rows()) {
		myfile << "|";
		for (size_t i = 0; i < searched_table.get_num_of_columns(); i++) {
			std::cout << searched_table.get_column(i).get_row(counter);
			if (searched_table.get_column(i).get_row(counter).length() < 20) {
				for (size_t g = 0; g < 20 - searched_table.get_column(i).get_row(counter).length(); g++) {
					myfile << " ";
				}
			}
			myfile << "|";
		}
		myfile << std::endl;
		for (size_t i = 0; i < searched_table.get_num_of_columns() * 19; i++) {
			myfile << "=";
		}
		myfile << std::endl;
		counter++;
	}

}
size_t Database::count(const std::string table_name, const size_t column_n,const std::string value) {
	Table searched_table;
	size_t counter = 0;
	searched_table.search_table(table_name, all_tables, number_of_tables);
	for (size_t i = 0; i < searched_table.get_num_of_columns(); i++) {
		if (searched_table.get_column(column_n).get_row(i) == value) {
			counter++;
		}
	}
	return counter;
}

void Database::update(const std::string table_name, const size_t column_n, const std::string value, const size_t target_column_n, const std::string target_value) {
	Table searched_table;
	searched_table.search_table(table_name, all_tables, number_of_tables);
	for (size_t i = 0; i < searched_table.get_num_of_columns(); i++) {
		if (searched_table.get_column(column_n).get_row(i) == value) {
			searched_table.get_column(target_column_n).set_row(target_value);
			break;
		}
	}
}
