#include "Database.h"
#include<fstream>
void Database::showtables() {
	for (size_t i = 0; i < number_of_tables; i++) {
		all_tables[i].print();
	}
}
void Database::import(const std::string filename) {
	Table new_table;
	new_table.Read_from_file(filename);
	number_of_tables++;
	number_of_files++;
	//new_table.add<Table>(all_tables, number_of_tables, new_table);
	Table* buff = new Table[number_of_tables];
	for (size_t i = 0; i < number_of_tables - 1; i++) {
		buff[i] = all_tables[i];
	}
	delete[] all_tables;
	all_tables = new Table[number_of_tables];
	for (size_t i = 0; i < number_of_tables - 1; i++) {
		all_tables[i] = buff[i];
	}
	delete[] buff;
	all_tables[number_of_tables - 1] = new_table;

	//new_table.add<std::string>(names_of_files, number_of_files, filename);
	
	std::string* buff2 = new std::string[number_of_files];
	for (size_t i = 0; i < number_of_files - 1; i++) {
		buff2[i] = names_of_files[i];
	}
	delete[] names_of_files;
	names_of_files = new std::string[number_of_tables];
	for (size_t i = 0; i < number_of_files - 1; i++) {
		names_of_files[i] = buff2[i];
	}
	delete[] buff2;
	names_of_files[number_of_files - 1] = filename;
}
void Database::describe(const std::string table_name) {
	Table searched_table;
	searched_table.search_table(table_name, all_tables, number_of_tables);
	searched_table.show_columnstypes();

}
void Database::print(const std::string table_name) {
	Table searched_table;
	searched_table.search_table(table_name,all_tables,number_of_tables);
		searched_table.print();
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
	//searched_table.add<Column>(searched_table.get_columns(), searched_table.get_num_of_columns(), new_column);
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
void Database::rename(const std::string old_name,const std::string new_name) {
	int index=-1;
	bool flag = false;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == old_name) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "There is no table with this name in the database!"<<std::endl;
	}
	else {
		for (size_t i = 0; i < number_of_tables; i++) {
			if (all_tables[i].get_name() == new_name) {
				flag = true;
				break;
			}
		}
		if (flag) {
			std::cout << "There is already a table with this name in the database!" << std::endl;
		}
		else {
			all_tables[index].set_name(new_name);
		}
	}
}

void Database::export_table(const std::string table_name, const std::string file_name){
	Table searched_table;
	searched_table.search_table(table_name, all_tables, number_of_tables);
	std::ofstream myfile;
	myfile.open(file_name, std::ios::out);
	for (size_t i = 0; i < searched_table.get_num_of_columns(); i++) {
		switch (searched_table.get_column(i).get_columtype()) {
		case type::Double: myfile << "Double" ;   break;
		case type::Integer: myfile << "Integer";   break;
		case type::String: myfile << "String";   break;
		case type::Null: myfile << "Null";   break;
		}
		if (i + 1 < searched_table.get_num_of_columns()) {
			myfile << ",";
		}
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
			//std::cout << searched_table.get_column(i).get_row(counter) << "|";
			myfile << searched_table.get_column(i).get_row(counter) << "|";
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
	myfile.close();
}
size_t Database::count(const std::string table_name, const size_t column_n,const std::string value) {
	Table searched_table;
	size_t counter = 0;
	searched_table.search_table(table_name, all_tables, number_of_tables);
	for (size_t i = 0; i < searched_table.get_num_of_columns(); i++) {
		if (searched_table.get_column(column_n-1).get_row(i) == value) {
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
