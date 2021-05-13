#include <iostream>
#include <fstream>
#include"Database.h"
using namespace std;
int main()
{

    Database d;
    std::cout << "Importing table and printing it."<<std::endl;
    d.import("Table1.txt");
    d.print("Table1");
    d.export_table("Table1", "Table1_exported.txt");
    d.import("Table1_exported.txt");
    d.rename("Table1", "Table1_export");
    std::cout << "Importing table after renaming exporting it to file."<<std::endl;
    d.showtables();
    std::cout << "Printing the columntypes of Table1_export." << std::endl;
    d.describe("Table1_export");
    d.import("Table2.txt");
    std::cout << "Importing table." << std::endl;
    d.showtables();
    std::cout << "Printing the rows where ""425"" is on second place." << std::endl;
    d.select(1, "425               ", "Table 2");
    d.addcolumn("Table 2", "Integer");
    std::cout << "Adding column to Table 2." << std::endl;
    d.showtables();
   // d.remove("Table 2",1, "425               " );
   // std::cout << "Deleting the cells from column2 whose value is ""425"""<< std::endl;
    //d.print("Table 2");
    std::cout << "Counting the cells from column2 whose value is ""425""" << std::endl;
    d.count("Table 2", 1, "425               ");
    std::cout << "Finding the cell from column2 whose value is ""1000"" and changing the cell on the same row from column3." << std::endl;
    d.update("Table 2", 1, "1000              ", 3, "Changed value");
    d.print("Table 2");

    std::cout << "Finding the cells from column1 whose value is ""abcd"" and applying operation to the same rows of column2." << std::endl;
    std::cout << "Sum: ";
    d.aggregate("Table 2", 0, "abcd              ", 1, "sum");
    std::cout << "Product: ";
    d.aggregate("Table 2", 0, "abcd              ", 1, "product");
    std::cout << "Minimum: ";
    d.aggregate("Table 2", 0, "abcd              ", 1, "minimum");
    std::cout << "Maximum: ";
    d.aggregate("Table 2", 0, "abcd              ", 1, "maximum");

    

        return 0;
}
