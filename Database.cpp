#include "Database.h"
#include<fstream>
Database::Database() {
	all_tables = nullptr;
	names_of_files = nullptr;
	number_of_files = 0;
	number_of_tables = 0;
}
Database::Database(Database& other) {
	this->all_tables = other.all_tables;
	this->names_of_files = other.names_of_files;
	this->number_of_files = other.number_of_files;
	this->number_of_tables = other.number_of_tables;
}
void Database::showtables() {
	std::cout << "DATABASE: " << std::endl << std::endl;
	for (size_t i = 0; i < number_of_tables; i++) {
		all_tables[i].print();
	}
}
void Database::import(const std::string& filename) {
	Table new_table;
	new_table.Read_from_file(filename);
	number_of_tables++;
	number_of_files++;
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
void Database::describe(const std::string& table_name) {
	Table searched_table;

	if(searched_table.search_table(table_name, all_tables, number_of_tables)){;
	searched_table.show_columnstypes();
	}
}
void Database::print(const std::string& table_name) {
	Table searched_table;
	if (searched_table.search_table(table_name, all_tables, number_of_tables)) {
		searched_table.print();
	}
}
void Database::select(const size_t column_n,std::string value,const std::string& table_name) {
	Table searched_table;
	if (searched_table.search_table(table_name, all_tables, number_of_tables)) {
		size_t num_of_c = searched_table.get_num_of_columns();
		size_t num_of_r = searched_table.get_column(0).get_number_of_rows();
		for (size_t i = 0 ; i < num_of_r ; i++) {
			std::string curr_row = searched_table.get_column(column_n).get_row(i);
			if (value.compare(remove_spaces(curr_row)) == 0) {
				for (size_t g = 0 ; g < num_of_c ; g++) {

					std::cout<<searched_table.get_column(g).get_row(i);
				}
				std::cout << std::endl;
			}
		}
	}
}

void Database::addcolumn(const std::string& table_name,const std::string& column_type) {
	size_t index = find_table(table_name);
	if(index != -1) {
		Column new_column;
		size_t num_of_r = all_tables[index].get_column(0).get_number_of_rows();
		size_t num_of_c = all_tables[index].get_num_of_columns();
		new_column.set_columtype(column_type);
		all_tables[index].set_num_of_columns(num_of_c + 1);
		num_of_c++;
		for (size_t g = 0; g < num_of_r; g++) {
			new_column.new_row("");
		}
		Column* buff = new Column[num_of_c];
		for (size_t i = 0; i < num_of_c - 1; i++) {
			buff[i] = all_tables[index].get_column(i);
		}
		all_tables[index].destroy_columns();
		all_tables[index].new_columns(num_of_c);
		for (size_t i = 0; i < num_of_c - 1; i++) {
			all_tables[index].set_column(i,buff[i]);
		}
		delete[] buff;
		all_tables[index].set_column(num_of_c - 1, new_column);
	}

}
void Database::remove(const std::string& table_name, const size_t column_n,const std::string& value) {
	size_t index = find_table(table_name);
	if (index != -1) {
		size_t num_of_r = all_tables[index].get_column(column_n).get_number_of_rows();
		for (size_t i = 0; i < num_of_r; i++) {
			if (remove_spaces(all_tables[index].get_column(column_n).get_row(i)) == value) {
				all_tables[index].get_column(column_n).set_row(i, "");
			}
		}
	}
}
void Database::rename(const std::string& old_name,const std::string& new_name) {
	size_t index = find_table(old_name);
	bool flag = false;
	if (index != -1) {
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

void Database::export_table(const std::string& table_name, const std::string& file_name){
	Table searched_table;
	if (searched_table.search_table(table_name, all_tables, number_of_tables)) {
		size_t num_of_c = searched_table.get_num_of_columns();
		size_t num_of_r = searched_table.get_column(0).get_number_of_rows();
		std::ofstream myfile;
		myfile.open(file_name, std::ios::out);
		for (size_t i = 0; i < num_of_c; i++) {

			switch (searched_table.get_column(i).get_columtype()) {
			case type::Double: myfile << "Double"; break;
			case type::Integer: myfile << "Integer"; break;
			case type::String: myfile << "String"; break;
			case type::Null: myfile << "Null"; break;
			}
			if (i + 1 < num_of_c) {
				myfile << ",";
			}
		}
		myfile << std::endl;
		myfile << searched_table.get_name() << std::endl;
		size_t counter = 0;
		for (size_t i = 0; i < num_of_c * 21; i++) {
			myfile << "=";
		}
		myfile << std::endl;
		while (counter < num_of_r) {
			myfile << "|";
			for (size_t i = 0; i < num_of_c; i++) {
				myfile << searched_table.get_column(i).get_row(counter);
				if (searched_table.get_column(i).get_row(counter).length() < 20) {
					size_t len = searched_table.get_column(i).get_row(counter).length();
					for (size_t g = 0; g < 20 - len; g++) {
						myfile << " ";
					}
				}
				myfile << "|";
			}
			myfile << std::endl;
			for (size_t i = 0; i < num_of_c * 21; i++) {
				myfile << "=";
			}
			myfile << std::endl;
			counter++;
		}
		myfile.close();
	}
}
void Database::count(const std::string& table_name, const size_t column_n,const std::string& value) {
	size_t counter = 0;
	size_t index = find_table(table_name);
	if (index != -1) {
		size_t num_of_r = all_tables[index].get_column(column_n).get_number_of_rows();
		for (size_t i = 0; i < num_of_r; i++) {
			if (remove_spaces(all_tables[index].get_column(column_n).get_row(i)) == value) {
				counter++;
			}
		}
	}
	std::cout<< counter<<std::endl;
}

void Database::update(const std::string& table_name, const size_t column_n, const std::string& value, const size_t target_column_n, const std::string& target_value) {
	size_t index = find_table(table_name);
	if (index != -1) {
		size_t num_of_r = all_tables[index].get_column(column_n).get_number_of_rows();
		for (size_t i = 0; i < num_of_r; i++) {
			if (remove_spaces(all_tables[index].get_column(column_n).get_row(i)) == value) {
				all_tables[index].get_column(target_column_n).set_row(i, target_value);
			}
		}
	}
}
void Database::aggregate(const std::string& table_name, const size_t column_n,const std::string& value, const size_t target_column_n, const std::string& operation) {
	double result=0;
	bool flag = true;
	if (operation != "sum" && operation != "product" && operation != "maximum" && operation != "minimum") {
		std::cout << "Invalid operation!"<<std::endl;
	}
	else {
		size_t index = find_table(table_name);
		if (index != -1) {
			if (all_tables[index].get_column(target_column_n).get_columtype() != type::Integer&& all_tables[index].get_column(target_column_n).get_columtype() != type::Double) {
				std::cout << "The target's columntype is not Integer or Double!"<<std::endl;
			}
			else {
				for (size_t i = 0; i < all_tables[index].get_column(column_n).get_number_of_rows(); i++) {
					if (remove_spaces(all_tables[index].get_column(column_n).get_row(i)) == value) {
						if (all_tables[index].get_column(target_column_n).get_columtype() == type::Integer) {
							if (flag) {
								result = all_tables[index].get_column(target_column_n).string_to_int(all_tables[index].get_column(target_column_n).get_row(i));
								flag = false;
							}
							else {
								
									if (operation == "sum") {
										result += all_tables[index].get_column(target_column_n).string_to_int(all_tables[index].get_column(target_column_n).get_row(i));
									}
									else if (operation == "product") {

										result *= all_tables[index].get_column(target_column_n).string_to_int(all_tables[index].get_column(target_column_n).get_row(i));
									}
									else if (operation == "maximum") {
										if (all_tables[index].get_column(target_column_n).string_to_int(all_tables[index].get_column(target_column_n).get_row(i)) > result) {


											result = all_tables[index].get_column(target_column_n).string_to_int(all_tables[index].get_column(target_column_n).get_row(i));
										}
									}
									else if (operation == "minimum") {
										if (all_tables[index].get_column(target_column_n).string_to_int(all_tables[index].get_column(target_column_n).get_row(i)) < result) {


											result = all_tables[index].get_column(target_column_n).string_to_int(all_tables[index].get_column(target_column_n).get_row(i));
										}

									}
							}
						}
						else {
							if (flag) {
								result = all_tables[index].get_column(target_column_n).string_to_double(all_tables[index].get_column(target_column_n).get_row(i));
								flag = false;
							}
							else {

								if (operation == "sum") {
									result += all_tables[index].get_column(target_column_n).string_to_double(all_tables[index].get_column(target_column_n).get_row(i));
								}
								else if (operation == "product") {

									result *= all_tables[index].get_column(target_column_n).string_to_double(all_tables[index].get_column(target_column_n).get_row(i));
								}
								else if (operation == "maximum") {
									if (all_tables[index].get_column(target_column_n).string_to_double(all_tables[index].get_column(target_column_n).get_row(i)) > result) {


										result = all_tables[index].get_column(target_column_n).string_to_double(all_tables[index].get_column(target_column_n).get_row(i));
									}
								}
								else if (operation == "minimum") {
									if (all_tables[index].get_column(target_column_n).string_to_double(all_tables[index].get_column(target_column_n).get_row(i)) < result) {


										result = all_tables[index].get_column(target_column_n).string_to_double(all_tables[index].get_column(target_column_n).get_row(i));
									}

								}
							}

						}
					}
				}
			}
		}
		std::cout << result<<std::endl;
	}
	
}
std::string Database::remove_spaces(std::string str) {
	std::string buff;
	const size_t length = str.length();
	for (size_t i = 0; i < length - 1; i++) {
		if (str[i] == ' ' && str[i + 1] == ' ') {
			buff.resize(i);
			for (size_t g = 0; g < i; g++) {
				buff[g] = str[g];
			}
			break;
		}
	}
	return buff;
}
int Database::find_table(const std::string& table_name) {
	int index = -1;
	for (size_t i = 0; i < number_of_tables; i++) {
		if (all_tables[i].get_name() == table_name) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "There is no table with this name in the database!" << std::endl;
	}
	return index;
}

void Database::menu_options_out() {
	std::cout << "MENU:" << std::endl;
	std::cout << "1.Import table from file. " << std::endl;
	std::cout << "2.Show tables in database. " << std::endl;
	std::cout << "3.Describe table (returns the types of the columns). " << std::endl;
	std::cout << "4.Print selected table." << std::endl;
	std::cout << "5.Select. " << std::endl;
	std::cout << "6.Add empty column to table." << std::endl;
	std::cout << "7.Update " << std::endl;
	std::cout << "8.Delete cell." << std::endl;
	std::cout << "9.Insert row in table." << std::endl;
	std::cout << "10.Inner join of two tables." << std::endl;
	std::cout << "11.Rename table." << std::endl;
	std::cout << "12.Count cells." << std::endl;
	std::cout << "13.Aggregate." << std::endl;
	std::cout << "h-Help  " << "o-Open  " << "s-Save  " << "c-Close  " << "e-Exit" << std::endl << std::endl;
}

void Database::menu() {
	menu_options_out();
	std::string input = "";
	std::string target_value, value, c_type, c_name, f_name, t_name, opened_table, operation, opened_file;
	size_t column_n, target_column_n, input_int;
	std::vector <std::string> column_value;
	std::cout << "Open table from the database before selecting any other funtions." << std::endl;
	showtables();
	while (input != "e") {
		std::cin >> input;
		if (input == "1") { std::cin >> f_name; import(f_name); }
		else if (input == "2") {
			showtables();
		}
		else if (input == "3") {
			describe(opened_file);
		}
		else if (input == "4") {
			print(opened_table);
		}
		else if (input == "5") {
			std::cout << "Enter: <num of column>(int) <value to search>" << std::endl;
			std::cin >> column_n >> value;
			select(column_n, value, opened_table);
		}
		else if (input == "6") {
			std::cout << "Enter: <column name> <column type>" << std::endl;
			std::cin >> c_name >> c_type;
			addcolumn(opened_table, c_type);
		}
		else if (input == "7") {
			std::cout << "Enter: <num of column>(int) <value to search> <num of the target column> <target value>: " << std::endl;
			std::cin >> column_n >> value >> target_column_n >> target_value;
			update(opened_table, column_n, target_value, target_column_n, target_value);
		}
		else if (input == "8") {
			std::cout << "Enter: <num of column>(int) <value to search>" << std::endl;
			std::cin >> column_n >> value;
			remove(opened_table, column_n, value);
		}
		else if (input == "9") {
			std::cin >> column_n >> value;
		}
		else if (input == "10") {
			std::cin >> column_n >> t_name >> target_column_n;
		}
		else if (input == "11") {
			std::cout << "Enter: <new name of the table>" << std::endl;
			std::cin >> t_name;
			rename(opened_table, t_name);
		}
		else if (input == "12") {
			std::cout << "Enter: <num of column>(int) <value to search>" << std::endl;
			std::cin >> column_n >> value;
			count(opened_table, column_n, value);
		}
		else if (input == "13") {
			std::cout << "Enter: <num of column>(int) <value to search> <num of target column>(int) <operation>(sum,minimum,maximum or product)" << std::endl;
			std::cin >> column_n >> value >> target_column_n >> operation; aggregate(opened_table, column_n, value, target_column_n, operation);
		}
		else if (input == "h") {
			menu_options_out();
		}
		else if (input == "o") {
			std::cin >> t_name;
			if (find_table(t_name) != -1) {
				opened_table = t_name;
			}
		}
		else if (input == "s") {
			std::cin >> f_name;
			export_table(opened_table, f_name);
		}
		else if (input == "c") {
			opened_table.clear();
			opened_table = "";
		}
		else if (input != "e") {
			std::cout << "Invalid input.";
		}
	}

}
