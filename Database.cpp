#include "Database.h"
#include<fstream>

Database::Database() {
	std::ofstream myfile;
	myfile.open("catalogue.txt", std::ios::trunc);
	myfile.close();
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

size_t Database::get_num_of_files()const {
	return number_of_files;
}
size_t Database::get_num_of_tables()const {
	return number_of_tables;
}
Table& Database::get_table(const size_t index) {
	return all_tables[index];
}

//Принтира всички таблици в базата от данни.
void Database::showtables() {
	std::cout << "DATABASE: " << std::endl << std::endl;
	for (size_t i = 0; i < number_of_tables; i++) {
		all_tables[i].print();
	}
} 

//Добавя таблица от подадено име на файл.
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
	export_table(all_tables[number_of_tables - 1].get_name(), "Catalogue.txt", true);
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

//Принтира типовете на всички колни на таблицата.
void Database::describe(const std::string& table_name) {
	Table searched_table;
	if(searched_table.search_table(table_name, all_tables, number_of_tables)){;
	searched_table.show_columnstypes();
	}
	std::cout << std::endl;
}

//Принтира таблица.
void Database::print(const std::string& table_name) {
	Table searched_table;
	if (searched_table.search_table(table_name, all_tables, number_of_tables)) {
		searched_table.print_with_pages();
	}
}

//Принтира редовете, чиито колона с номер N има стойност "value".
void Database::select(size_t column_n,const std::string& value,const std::string& table_name) {
	column_n--;
	Table searched_table;
	if (searched_table.search_table(table_name, all_tables, number_of_tables)) {
		size_t num_of_c = searched_table.get_num_of_columns();
		size_t num_of_r = searched_table.get_column(0).get_number_of_rows();
		for (size_t i = 0 ; i < num_of_r ; i++) {
			std::string curr_row = searched_table.get_column(column_n).get_row(i);
			if (value.compare(remove_spaces(curr_row)) == 0) {
				for (size_t g = 0 ; g < num_of_c ; g++) {
					std::cout << " | " << remove_spaces(searched_table.get_column(g).get_row(i));
				}
				std::cout << std::endl;
			}
		}
	}
}

//Добавя нова колона с първи ред подаденото име, а останалите редове са празни. 
void Database::addcolumn(const std::string& table_name, const std::string& columns_name,const std::string& column_type) {
	size_t index = find_table(table_name);
	if(index != -1) {
		Column new_column;
		size_t num_of_r = all_tables[index].get_column(0).get_number_of_rows();
		size_t num_of_c = all_tables[index].get_num_of_columns();
		new_column.set_columtype(column_type);
		all_tables[index].set_num_of_columns(num_of_c + 1);
		num_of_c++;
		new_column.new_row(columns_name);
		for (size_t g = 1; g < num_of_r; g++) {
			new_column.new_row("NULL");
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

//При намиране на стойност "value" на колоната N, функцията изтрива тази клетка.
void Database::remove(const std::string& table_name, size_t column_n,const std::string& value) {
	column_n--;
	size_t index = find_table(table_name);
	if (index != -1) {
		size_t num_of_r = all_tables[index].get_column(column_n).get_number_of_rows();
		for (size_t i = 0; i < num_of_r; i++) {
			if (remove_spaces(all_tables[index].get_column(column_n).get_row(i)) == value) {
				all_tables[index].get_column(column_n).set_row(i, "NULL");
			}
		}
	}
}

//Добавя нов ред в таблицата с подадените на функцията стойности.
void Database::insert(const std::string& table_name, const std::string* arr,const size_t& size_of_arr, const size_t& index) {
	for (size_t i = 0; i < size_of_arr; i++) {
		all_tables[index].get_column(i).new_row(arr[i]);
	}
}

//Прави inner join на две таблици.
void Database::innerjoin(const std::string& table_1, size_t column_num_1, const std::string& table_2, size_t column_num_2) {
	column_num_1--;
	column_num_2--;
	Table innerjoined_table;
	bool flag = true, flag2=true;
	size_t index_of_table1, index_of_table2, rows_column1, rows_column2,counter=0,columns_table1, columns_table2;
	index_of_table1 = find_table(table_1);
	index_of_table2 = find_table(table_2);
	rows_column1 = all_tables[index_of_table1].get_column(column_num_1).get_number_of_rows();
	rows_column2 = all_tables[index_of_table2].get_column(column_num_2).get_number_of_rows();
	columns_table1 = all_tables[index_of_table1].get_num_of_columns();
	columns_table2 = all_tables[index_of_table2].get_num_of_columns();
	for (size_t i = 0; i < rows_column1; i++) {
		for (size_t g = 0; g < rows_column1; g++) {
			if (all_tables[index_of_table1].get_column(column_num_1).get_row(i) == all_tables[index_of_table2].get_column(column_num_2).get_row(g)) {
				if (flag) {
					innerjoined_table.new_columns(columns_table1 + columns_table2 - 1);
					innerjoined_table.set_num_of_columns(columns_table1 + columns_table2 - 1);
					flag = false;
				}
				for (size_t j = 0; j < columns_table1; j++) {
					innerjoined_table.get_column(counter).new_row(all_tables[index_of_table1].get_column(j).get_row(i));
					if (flag2) {
						innerjoined_table.get_column(counter).set_columtype(enum_to_string(all_tables[index_of_table1].get_column(j).get_columtype()));
					}
					counter++;
					
				}
				for (size_t j = 0; j < columns_table2; j++) {
					if (j == column_num_2) {
						j++;
						if (j == columns_table2) {
							break;
						}
					}
					innerjoined_table.get_column(counter).new_row(all_tables[index_of_table2].get_column(j).get_row(g));
					if (flag2) {
						innerjoined_table.get_column(counter).set_columtype(enum_to_string(all_tables[index_of_table2].get_column(j).get_columtype()));
					}
					counter++;
				}
				flag2 = false;
			}
			counter = 0;
		}
	}
	innerjoined_table.set_name("Innerjoined table");
	innerjoined_table.print_with_pages();
	std::cout << "Do you want to save the table?(y-Yes/n-No) ";
	std::string input;
	std::cin >> input;
	if (input == "y") {
		std::cout << "Enter file for the export ";
		std::cin >> input;
		innerjoined_table.export_to_file(input);
	}
	else if (input != "n") {
		std::cout << "Incorect comand.Please enter y-Yes/n-No. ";
	}
}

//Преименува таблица.
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

//Записва таблицата във файл, чието име е подадено на функцията.
void Database::export_table(const std::string& table_name, const std::string& file_name, const bool& flag){
	Table searched_table;
	if (searched_table.search_table(table_name, all_tables, number_of_tables)) {
		size_t num_of_c = searched_table.get_num_of_columns();
		size_t num_of_r = searched_table.get_column(0).get_number_of_rows();
		std::ofstream myfile;
		if (flag) {
			myfile.open(file_name, std::ios::app);
		}
		else {
			myfile.open(file_name, std::ios::out);
		}
		for (size_t i = 0; i < num_of_c; i++) {

			switch (searched_table.get_column(i).get_columtype()) {
			case type::Double: myfile << "Double"; break;
			case type::Integer: myfile << "Integer"; break;
			case type::String: myfile << "String"; break;
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

//Извежда броя на клетките със стойност "value" на колкона N.
void Database::count(const std::string& table_name, size_t column_n,const std::string& value) {
	column_n--;
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

//Намира клетките със стойност "value" от колона N и променя стойноста на клетките от същите редове на колона target_N (променя я на "target_value").
void Database::update(const std::string& table_name, size_t column_n, const std::string& value, size_t target_column_n, const std::string& target_value) {
	column_n--;
	target_column_n--;
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

//Намира клетките със стойност "value" от колона N и прилага "operation" на клетките от същия ред на колона target_N.
void Database::aggregate(const std::string& table_name, size_t column_n,const std::string& value, size_t target_column_n, const std::string& operation) {
	column_n--;
	target_column_n--;
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
								result = all_tables[index].get_column(target_column_n).string_to_double(remove_spaces(all_tables[index].get_column(target_column_n).get_row(i)));
								flag = false;
							}
							else {

								if (operation == "sum") {
									result += all_tables[index].get_column(target_column_n).string_to_double(remove_spaces(all_tables[index].get_column(target_column_n).get_row(i)));
								}
								else if (operation == "product") {

									result *= all_tables[index].get_column(target_column_n).string_to_double(remove_spaces(all_tables[index].get_column(target_column_n).get_row(i)));
								}
								else if (operation == "maximum") {
									if (all_tables[index].get_column(target_column_n).string_to_double(remove_spaces(all_tables[index].get_column(target_column_n).get_row(i))) > result) {


										result = all_tables[index].get_column(target_column_n).string_to_double(remove_spaces(all_tables[index].get_column(target_column_n).get_row(i)));
									
									}
								}
								else if (operation == "minimum") {
									if (all_tables[index].get_column(target_column_n).string_to_double(remove_spaces(all_tables[index].get_column(target_column_n).get_row(i))) < result) {


										result = all_tables[index].get_column(target_column_n).string_to_double(remove_spaces(all_tables[index].get_column(target_column_n).get_row(i)));
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

//Принтира опциите на менюто.
void Database::print_menu_options() {
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
	std::cout << "h-Help  " << "o-Open  " << "s-Save " << "sa-SaveAs  " << "c-Close  " << "e-Exit" << std::endl << std::endl;
}

//Ръководи функционалностите на програмата.
void Database::menu() {
	print_menu_options();
	std::string input = "";
	std::string target_value="", value="", c_type="", c_name="", f_name="", t_name="", opened_table="", operation="", opened_file="";
	size_t column_n, target_column_n, columns_of_opened_table = 0;

	std::cout << "Open table from the database before selecting any other funtions." << std::endl;
	showtables();

	while (input != "e") {
		std::cout << "Enter comand from the menu (Write ""h"" to see the menu options) ";
		std::cin >> input;
		if (input == "1") { 
			std::cout << "Enter filename(*.txt) ";
			std::cin >> f_name; 
			import(f_name); 
			std::cout << "The table is imported."<<std::endl;
		}
		else if (input == "2") {
			showtables();
		}
		else if (input == "h") {
			print_menu_options();
		}
		else if (input == "o") {
			std::cout << "Enter tablename from the database(";
			for (size_t i = 0; i < number_of_tables; i++) {
				std::cout << all_tables[i].get_name();
				if (i + 1 < number_of_tables) {
					std::cout << ", ";
				}
			}
			std::cout << ") ";
			std::cin.ignore();
			std::getline(std::cin, t_name);
			int index_of_table = find_table(t_name);
			if (index_of_table != -1) {
			opened_table = t_name;
			opened_file = names_of_files[index_of_table];
			columns_of_opened_table = all_tables[index_of_table].get_num_of_columns();
				std::cout << opened_table<<" is opened."<<std::endl;
			}
		}
		else if (!if_table_is_opened(opened_table)) {
			std::cout << "There is no opened table."<<std::endl;
		}
		else if (input == "3") {
			std::cout << "The columntypes are:";
			describe(opened_table);
		}
		else if (input == "4") {
			print(opened_table);
		}
		else if (input == "5") {
			std::cout << "Enter: <num of column>(int) <value to search>" << std::endl;
			std::cin >> column_n;
			column_input_validation(column_n, columns_of_opened_table);
			std::cin.ignore();
			std::getline(std::cin, value);
			value_input_validation(value, 20);
			select(column_n, value, opened_table);
		}
		else if (input == "6") {
			std::cout << "Enter: <column name> <column type>" << std::endl;

			std::cin.ignore();
			std::getline(std::cin, c_name);
			value_input_validation(c_name, 20);
			std::cin >> c_type;
			columntype_input_validation(c_type);
			addcolumn(opened_table, c_name, c_type);
		}
		else if (input == "7") {
			std::cout << "Enter: <num of column>(int) <value to search> <num of the target column> <target value>: " << std::endl;
			std::cin >> column_n;
			column_input_validation(column_n, columns_of_opened_table);
			std::cin.ignore();
			std::getline(std::cin, value);
			value_input_validation(value, 20);
			std::cin >> target_column_n;
			column_input_validation(target_column_n, columns_of_opened_table);
			std::cin.ignore();
			std::getline(std::cin, target_value);
			value_input_validation(target_value, 20);
			update(opened_table, column_n, value, target_column_n, target_value);
		}
		else if (input == "8") {
			std::cout << "Enter: <num of column>(int) <value to search>" << std::endl;
			std::cin >> column_n;
			column_input_validation(column_n, columns_of_opened_table);
			std::cin.ignore();
			std::getline(std::cin, value);
			value_input_validation(value, 20);
			remove(opened_table, column_n, value);
		}
		else if (input == "9") {
			size_t index = find_table(opened_table);
			size_t size = all_tables[index].get_num_of_columns();
			std::string* column_values = new std::string[size];
			std::cout << "Enter:"<<size<<"<column values>";
			std::cin.ignore();
			for (size_t i = 0; i < size; i++) {
				std::getline(std::cin,column_values[i]);
				value_input_validation(column_values[i], 20);
			}
			insert(opened_table, column_values, size, index);
			delete[] column_values;
		}
		else if (input == "10") {
			std::cout << "Enter: <num of column from table 1>(int) <table_name> <num of column from table 2>: " << std::endl;
			std::cin >> column_n;
			column_input_validation(column_n, columns_of_opened_table);
			std::cin.ignore();
			std::getline(std::cin, t_name);
			std::cin>> target_column_n;
			column_input_validation(target_column_n, all_tables[find_table(t_name)].get_num_of_columns());
			innerjoin(opened_table, column_n, t_name, target_column_n);
		}
		else if (input == "11") {
			std::cout << "Enter: <new name of the table>" << std::endl;
			std::cin.ignore();
			std::getline(std::cin,t_name);
			rename(opened_table, t_name);
			opened_table = t_name;
		}
		else if (input == "12") {
			std::cout << "Enter: <num of column>(int) <value to search>" << std::endl;
			std::cin >> column_n;
			column_input_validation(column_n, columns_of_opened_table);
			std::cin.ignore();
			std::getline(std::cin, value);
			value_input_validation(value, 20);
			count(opened_table, column_n, value);
		}
		else if (input == "13") {
			std::cout << "Enter: <num of column>(int) <value to search> <num of target column>(int) <operation>(sum,minimum,maximum or product)" << std::endl;
			std::cin >> column_n;
			column_input_validation(column_n, columns_of_opened_table);
			std::cin.ignore();
			std::getline(std::cin, value);
			value_input_validation(value, 20);
			std::cin >> target_column_n;
			column_input_validation(column_n, columns_of_opened_table); 
			std::cin >> operation;

			aggregate(opened_table, column_n, value, target_column_n, operation);
		}
		else if (input == "s") {
			export_table(opened_table, opened_file);
			std::cout << "The table is saved."<<std::endl;
		}
		else if (input == "sa") {
			std::cout << "Enter filename for the export (*.txt) ";
			std::cin >> f_name;
			export_table(opened_table, f_name);
			std::cout << "The table is saved in" << f_name<<"."<< std::endl;
		}
		else if (input == "c") {
			opened_table.clear();
			opened_table = "";
			std::cout << "The table is closed." << std::endl;
		}
		else if (input != "e") {
			std::cout << "Invalid input."<<std::endl;
		}
	}
}

//Проверява дали потребителят е отворил таблица, върху която да прилага функционалностите.
bool Database::if_table_is_opened(const std::string& table_name) {
	return !(table_name == "");
}

//Премахва излишните спейсове от клетката, които са добавени с цел добра визуализация на таблицата.
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

//Намира таблица в базата данни и връща нейния индекс. Ако не съществува такава таблица, функцията връща -1 и извежда съобщение за невалидно име.
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

//Преобразува прочетения от файл string към enum.
std::string Database::enum_to_string(const type& type_of_c) {
	std::string col_type;
	if (type_of_c == type::Double) {
		col_type = "Double";
	}
	else if (type_of_c == type::Integer) {
		col_type = "Integer";
	}
	else if (type_of_c == type::String) {
		col_type = "String";
	}
	return col_type;
}

//Валидира стойносста на клетката, която е подадена от потребителя.
void Database::value_input_validation(std::string& input, const size_t& size) {
	while (input.size() > size) {
		std::cout << "Invalid input. (max " << size << " symbols)";
		std::cin.ignore();
		std::getline(std::cin, input);
	}
}

//Проверява дали подадения номер на колона съществува.
void Database::column_input_validation(size_t& input, const size_t& size) {
	while (input > size || input <= 0) {
		std::cout << "Invalid input.There is "<<size<<" columns in the table.";
		std::cin >> input;
	}
}

//Проверява дали подадения тип на колоната се поддържа от програмата.
void Database::columntype_input_validation(std::string& input) {
	while (input != "String" && input != "Integer" && input != "Double") {
		std::cout << "Invalid columntype.(types: Integer, Double or String)";
		std::cin >> input;
	}
}
