#include <iostream>
#include"Database.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include"doctest.h"

TEST_CASE("Import function test") {
    Database d;
    CHECK(d.get_num_of_files() == 0);
    CHECK(d.get_num_of_tables() == 0);

    d.import("Table1.txt");
    CHECK(d.get_num_of_files() == 1);
    CHECK(d.get_num_of_tables() == 1);
    
    d.import("Table2.txt");
    CHECK(d.get_num_of_files() == 2); 
    CHECK(d.get_num_of_tables() == 2);
    CHECK(d.get_table(0).get_name() == "Car List");
    CHECK(d.get_table(1).get_name() == "Drivers");
}

TEST_CASE("Update function test") {
    Database d;
    d.import("Table1.txt");
    d.update("Car List", 4, "2009", 5 , "Changed value");

    CHECK(d.get_table(0).get_column(4).get_row(1) == "Changed value");
    CHECK(d.get_table(0).get_column(4).get_row(3) == "Changed value");
}

TEST_CASE("Remove function test") {
    Database d;
    d.import("Table1.txt");
    d.remove("Car List", 4, "2009");

    CHECK(d.get_table(0).get_column(3).get_row(1) == "NULL");
    CHECK(d.get_table(0).get_column(3).get_row(3) == "NULL");
}

TEST_CASE("Addcolumn function test") {
    Database d;
    d.import("Table1.txt");
    d.import("Table2.txt");
    d.addcolumn("Car List", "New column", "Integer");

    CHECK(d.get_table(0).get_num_of_columns() == 10);
    CHECK(d.get_table(0).get_column(9).get_row(0) == "New column");
    CHECK(d.get_table(0).get_column(9).get_row(1) == "NULL");
    CHECK(d.get_table(0).get_column(9).get_row(4) == "NULL");
}

TEST_CASE("Rename function test") {
    Database d;
    d.import("Table1.txt");
    d.rename("Car List", "New name");
    CHECK(d.get_table(0).get_name() == "New name");
}

TEST_CASE("Insert function test") {
    Database d;
    std::string rows_values[9]{ "Column 1","Column 2","Column 3","Column 4","Column 5","Column 6","Column 7","Column 8","Column 9" };
    d.import("Table1.txt");
    d.insert("Car List", rows_values, 9 , 0);
    
    CHECK(d.get_table(0).get_column(0).get_number_of_rows() == 6);
    CHECK(d.get_table(0).get_column(0).get_row(5) == "Column 1");
    CHECK(d.get_table(0).get_column(3).get_row(5) == "Column 4");
    CHECK(d.get_table(0).get_column(8).get_row(5) == "Column 9");
}

int main()
{
    doctest::Context().run();
    Database d;
    d.import("Table1.txt");
    d.import("Table2.txt");
    d.import("Table3.txt");

    /*
    //Testing innerjoin function
    std::cout << "Table ""Car List"" and table ""Drivers"" innerjoin::" << std::endl;
    d.innerjoin("Car List", 9 , "Drivers", 1);
    std::cout << std::endl;

    //Testing select function
    std::cout << "Printing the the rows where ""2009"" is on 4th place." << std::endl;
    d.select(4, "2009", "Car List");
    std::cout << std::endl;

    //Testing describe function
    std::cout << "Printing the columntypes of ""Accounting""." << std::endl;
    d.describe("Accounting");
    std::cout << std::endl;

    //Testing count function
    std::cout << "Counting the cells from column2 whose value is ""425""" << std::endl;
    d.count("Car List", 4, "2009");
    std::cout << std::endl;

    //Testing aggregate function
    std::cout << "Finding the cells from column3 whose value is ""-16000"" and applying operation to the same rows of column4/column2." << std::endl;
    std::cout << "Sum: ";
    d.aggregate("Accounting", 3, "-16000", 4, "sum");
    std::cout << "Product: ";
    d.aggregate("Accounting", 3, "-16000", 4, "product");
    std::cout << "Minimum: ";
    d.aggregate("Accounting", 3, "-16000", 2, "minimum");
    std::cout << "Maximum: ";
    d.aggregate("Accounting", 3, "-16000", 4, "maximum");
    std::cout << std::endl;
    */

    d.menu();

    return 0;
}
