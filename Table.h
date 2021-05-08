#include "Column.h"
class Table {
private:
	MyString name;
	size_t number_of_colums;
	Column* columns;
public:
	void print();
};