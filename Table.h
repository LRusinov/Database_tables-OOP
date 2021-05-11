#include "Column.h"
class Table {
private:
	std::string name;
	size_t number_of_columns;
	Column* columns;
public:
	Table();
	~Table();
	void set_name(const std::string new_name);
	std::string get_name()const;
	Column* get_columns()const;
	Column get_column(const size_t n)const;
	size_t get_num_of_columns()const;
	void print();
	void Read_from_file(std::ifstream&  myfile);
	template<typename T>
	T add(T* arr, const size_t size_of_arr, const T element_to_add);
	void show_columnstypes();
	void search_rows(const size_t n, const std::string value);
	Table& search_table(const std::string name,const Table* tables, const size_t num_of_tables);
	Table& operator=(const Table& other);
};
