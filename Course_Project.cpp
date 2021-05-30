#include <iostream>
#include <fstream>
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
    CHECK(d.get_table(1).get_name() == "Table 2");
}

TEST_CASE("Update function test") {
    Database d;
    d.import("Table1.txt");
    d.update("Car List", 3, "2009", 4 , "Changed value");

    CHECK(d.get_table(0).get_column(4).get_row(1) == "Changed value");
    CHECK(d.get_table(0).get_column(4).get_row(3) == "Changed value");
}

TEST_CASE("Remove function test") {
    Database d;
    d.import("Table1.txt");
    d.remove("Car List", 3, "2009");

    CHECK(d.get_table(0).get_column(3).get_row(1) == "NULL");
    CHECK(d.get_table(0).get_column(3).get_row(3) == "NULL");
}
TEST_CASE("Addcolumn function test") {
    Database d;
    d.import("Table1.txt");
    d.import("Table2.txt");
    d.addcolumn("Car List", "New column", "Integer");

    CHECK(d.get_table(0).get_num_of_columns() == 6);
    CHECK(d.get_table(0).get_column(5).get_row(0) == "New column");
    CHECK(d.get_table(0).get_column(5).get_row(1) == "NULL");
    CHECK(d.get_table(0).get_column(5).get_row(3) == "NULL");
}

TEST_CASE("Rename function test") {
    Database d;
    d.import("Table1.txt");
    d.rename("Car List", "New name");
    CHECK(d.get_table(0).get_name() == "New name");
}

int main()
{
    doctest::Context().run();
    Database d;
    //d.import("Table1.txt");
    //d.import("Table2.txt");
    //d.innerjoin("Car List", 2, "Table 2", 1);
    //std::cout << "Printing the rows where ""425"" is on second place." << std::endl;
    //d.select(1, "425", "Table 2");
    d.menu();
    /*
    d.export_table("Table1", "Table1_exported.txt");

    std::cout << "Printing the columntypes of Table1_export." << std::endl;
    d.describe("Table1_export");

    d.import("Table1_exported.txt");
    std::cout << "Importing table." << std::endl;
    d.showtables();

    std::cout << "Printing the rows where ""425"" is on second place." << std::endl;
    d.select(1, "425", "Table 2");

    std::cout << "Counting the cells from column2 whose value is ""425""" << std::endl;
    d.count("Table 2", 1, "425");

    std::cout << "Finding the cells from column1 whose value is ""abcd"" and applying operation to the same rows of column2." << std::endl;
    std::cout << "Sum: ";
    d.aggregate("Table 2", 0, "abcd", 1, "sum");
    std::cout << "Product: ";
    d.aggregate("Table 2", 0, "abcd", 1, "product");
    std::cout << "Minimum: ";
    d.aggregate("Table 2", 0, "abcd", 1, "minimum");
    std::cout << "Maximum: ";
    d.aggregate("Table 2", 0, "abcd", 1, "maximum");*/

    

        return 0;
}
