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
	std::ofstream f("x.txt");
	size_t index = -1;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == table_name) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "There is no table with this name in the database!" << std::endl;
	}
	else {
		for (size_t i = 0; i < all_tables[index].get_column(0).get_number_of_rows(); i++) {
			f<< all_tables[index].get_column(column_n).get_row(i) << "|" << value;
			std::cout << value.compare(all_tables[index].get_column(column_n).get_row(i));
			if (value.compare(all_tables[index].get_column(column_n).get_row(i))==0) {
				all_tables[index].get_column(column_n).print_row();
			}


		}
	}
	f.close();
}

void Database::addcolumn(std::string table_name, std::string column_type) {
	size_t index = -1;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == table_name) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "There is no table with this name in the database!" << std::endl;
	}
	else {
		Column new_column;
		new_column.set_columtype(column_type);
		//new_column.set_number_of_rows(all_tables[index].get_column(0).get_number_of_rows());
		all_tables[index].set_num_of_columns(all_tables[index].get_num_of_columns() + 1);
		for (size_t g = 0; g < all_tables[index].get_column(0).get_number_of_rows(); g++) {
			new_column.new_row("");
		}
		//searched_table.add<Column>(searched_table.get_columns(), searched_table.get_num_of_columns(), new_column);
		
		Column* buff = new Column[all_tables[index].get_num_of_columns()];
		for (size_t i = 0; i < all_tables[index].get_num_of_columns() - 1; i++) {
			buff[i] = all_tables[index].get_column(i);
		}
		all_tables[index].destroy_columns();
		all_tables[index].new_columns(all_tables[index].get_num_of_columns());

		for (size_t i = 0; i < all_tables[index].get_num_of_columns() - 1; i++) {
			all_tables[index].set_column(i,buff[i]);
		}
		delete[] buff;
		all_tables[index].set_column(all_tables[index].get_num_of_columns() - 1, new_column);
	}

}
void Database::remove(const std::string table_name, const size_t column_n, const std::string value) {
	size_t index = -1;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == table_name) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "There is no table with this name in the database!" << std::endl;
	}
	else {
		for (size_t i = 0; i < all_tables[index].get_num_of_columns(); i++) {
			if (all_tables[index].get_column(column_n).get_row(i) == value) {
				all_tables[index].get_column(column_n).delete_row(i);
			}
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
	for (size_t i = 0; i < searched_table.get_num_of_columns() * 21; i++) {
		myfile << "=";
	}
	myfile << std::endl;
	while (counter < searched_table.get_column(0).get_number_of_rows()) {
		myfile << "|";
		for (size_t i = 0; i < searched_table.get_num_of_columns(); i++) {
			myfile << searched_table.get_column(i).get_row(counter) ;
			if (searched_table.get_column(i).get_row(counter).length() < 20) {
				for (size_t g = 0; g < 20 - searched_table.get_column(i).get_row(counter).length(); g++) {
					myfile << " ";
				}
			}
			myfile << "|";
		}
		myfile << std::endl;
		for (size_t i = 0; i < searched_table.get_num_of_columns() * 21; i++) {
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
	size_t index = -1;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == table_name) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "There is no table with this name in the database!" << std::endl;
	}
	else {
		for (size_t i = 0; i < all_tables[index].get_num_of_columns(); i++) {
			if (all_tables[index].get_column(column_n).get_row(i) == value) {
				//all_tables[index].get_column(target_column_n).set_row(target_value);
				break;
			}
		}
	}
}
