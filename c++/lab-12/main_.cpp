#include <iostream>
#include <string>
#include <vector>
#include "database.h"

#include <iostream>
#include <sstream>
#include <fstream>

int main() {
    Table table1({
                     {"CustomerID", {"1", "2", "3", "4", "5"}},
                     {"CustomerName", {"Anna", "John", "David", "Emma", "Alex"}},
                     {"Age", {"31", "27", "35", "29", "33"}},
                     {"City", {"San Francisco", "Seattle", "New York", "Los Angeles", "Chicago"}},
                     {"PurchaseID", {"201", "202", "203", "204", "205"}},
                     {"Product", {"Phone", "Laptop", "Camera", "Headphones", "Tablet"}}
                 });

    Database base({
                      {"Customers", table1}
                  });

    std::string request = R"(CREATE TABLE Shops)";
    Table result = base.MakeRequest(request);

    Table expected = table1;


    return 0;
}
