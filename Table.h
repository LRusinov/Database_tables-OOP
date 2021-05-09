#include "Column.h"
class Table {
private:
	std::string name;
	size_t number_of_colums;
	Column* columns;
public:
	void print();
	void Read_from_file();
};
