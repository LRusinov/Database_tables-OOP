#include "Column.h"
class Table {
private:
	std::string name;
	size_t number_of_columns;
	Column* columns;
public:
	Table();
	//~Table();
	void set_name(const std::string& new_name);//
	std::string get_name()const;//

	void set_num_of_columns(const size_t n);
	size_t get_num_of_columns()const;//
	void set_column(const size_t n, const Column& column);
	Column& get_column(const size_t n)const;//
	void new_columns(const size_t size);
	Column* get_columns()const;
	void destroy_columns();
	void show_columnstypes();

	bool search_table(const std::string& name, const Table* tables, const size_t num_of_tables);//
	void print_with_pages();//
	void print();//
	void Read_from_file(const std::string&  file_name);//
	void export_to_file(const std::string& file_name);

	Table& operator=(const Table& other);//
	

};
