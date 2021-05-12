#include "Column.h"
class Table {
private:
	std::string name;
	size_t number_of_columns;
	Column* columns;
public:
	Table();
	//~Table();
	void set_name(const std::string new_name);//
	std::string get_name()const;//
	void set_num_of_columns(const size_t n);
	Column* get_columns()const;
	Column& get_column(const size_t n)const;//
	size_t get_num_of_columns()const;//
	void print();//
	void Read_from_file(const std::string  file_name);//
	template<typename T>
	void add(T* arr, const size_t size_of_arr, const T& element_to_add) {
		if (arr == nullptr&&size_of_arr==1) {
			arr = new T[1];
			arr[0] = element_to_add;
		}
		else {
			T* buff = new T[size_of_arr];
			for (size_t i = 0; i < size_of_arr - 1; i++) {
				buff[i] = arr[i];
			}
			delete[] arr;
			arr = new T[size_of_arr];
			for (size_t i = 0; i < size_of_arr - 1; i++) {
				arr[i] = buff[i];
			}
			delete[] buff;
			arr[size_of_arr - 1] = element_to_add;
		}
	}
	void show_columnstypes();
	void search_rows(const size_t n, const std::string value);
	Table& search_table(const std::string name,const Table* tables, const size_t num_of_tables);//
	Table& operator=(const Table& other);//
	void destroy_columns();
	void new_columns(const size_t size);
	void set_column(const size_t n, const Column column);
};
