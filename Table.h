#include "Column.h"
class Table {
private:
	std::string name;
	size_t number_of_colums;
	Column* columns;
public:
	std::string get_name()const;
	void print();
	void Read_from_file(std::ifstream&  myfile);
	template<typename T>
	T add(T* arr, const size_t size_of_arr, const T element_to_add);
	void show_columnstypes();
	void search_row(const size_t n, const std::string value);
};
