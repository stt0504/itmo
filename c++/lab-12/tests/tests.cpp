#include "database.h"
#include <gtest/gtest.h>

Table table1({
                 {"CustomerID", {"1", "2", "3", "4", "5"}},
                 {"CustomerName", {"Anna", "John", "David", "Emma", "Alex"}},
                 {"Age", {"31", "27", "35", "29", "33"}},
                 {"City", {"NULL", "Seattle", "New York", "Los Angeles", "Chicago"}},
                 {"PurchaseID", {"201", "202", "203", "204", "205"}},
             });

Table table2({
                 {"PurchaseID", {"301", "202", "203", "204", "305"}},
                 {"Product", {"Phone", "Laptop", "Camera", "Headphones", "Tablet"}},
                 {"Price", {"599", "1299", "699", "149", "799"}}
             });

Database base({
                  {"Customers", table1},
                  {"Purchases", table2}
              });

std::string request;

Table result;

Table expected;

TEST(DatabaseTests, SELECT_TEST) {
    request = R"(SELECT CustomerID, Age, City FROM Customers)";
    result = base.MakeRequest(request);
    expected = Table({
                         {"CustomerID", {"1", "2", "3", "4", "5"}},
                         {"Age", {"31", "27", "35", "29", "33"}},
                         {"City", {"NULL", "Seattle", "New York", "Los Angeles", "Chicago"}},
                     });
    EXPECT_EQ(result, expected);

    request = R"(SELECT * FROM Customers)";
    result = base.MakeRequest(request);
    expected = table1;
    EXPECT_EQ(result, expected);

    request = R"(SELECT * FROM)";
    EXPECT_THROW(base.MakeRequest(request), std::invalid_argument);
}

TEST(DatabaseTests, SELECT_WHERE_TEST) {
    request = R"(SELECT * FROM Customers
                WHERE Age > 30 AND City IS NOT NULL)";
    result = base.MakeRequest(request);
    expected = Table({
                         {"CustomerID", {"3", "5"}},
                         {"CustomerName", {"David", "Alex"}},
                         {"Age", {"35", "33"}},
                         {"City", {"New York", "Chicago"}},
                         {"PurchaseID", {"203", "205"}},
                     });
    EXPECT_EQ(result, expected);

    request = R"(SELECT * FROM Table
                WHERE Age > AND City IS NOT NULL)";
    EXPECT_THROW(base.MakeRequest(request), std::invalid_argument);
}

TEST(DatabaseTests, LEFT_JOIN) {
    request = R"(SELECT * FROM Customers
                LEFT JOIN Purchases ON PurchaseID = PurchaseID)";
    result = base.MakeRequest(request);
    expected = Table({
                         {"CustomerID", {"1", "2", "3", "4", "5"}},
                         {"CustomerName", {"Anna", "John", "David", "Emma", "Alex"}},
                         {"Age", {"31", "27", "35", "29", "33"}},
                         {"City", {"NULL", "Seattle", "New York", "Los Angeles", "Chicago"}},
                         {"PurchaseID", {"201", "202", "203", "204", "205"}},
                         {"PurchaseID", {"301", "202", "203", "204", "305"}},
                         {"Product", {"NULL", "Laptop", "Camera", "Headphones", "NULL"}},
                         {"Price", {"NULL", "1299", "699", "149", "NULL"}}
                     });
    EXPECT_EQ(result, expected);

    request = R"(SELECT * FROM Customers
                LEFT JOIN Purchases ON PurchaseID = Column)";
    EXPECT_THROW(base.MakeRequest(request), std::invalid_argument);
}

TEST(DatabaseTests, RIGHT_JOIN) {
    request = R"(SELECT * FROM Customers
                RIGHT JOIN Purchases ON PurchaseID = PurchaseID)";
    result = base.MakeRequest(request);
    expected = Table({
                         {"PurchaseID", {"301", "202", "203", "204", "305"}},
                         {"Product", {"Phone", "Laptop", "Camera", "Headphones", "Tablet"}},
                         {"Price", {"599", "1299", "699", "149", "799"}},
                         {"CustomerID", {"NULL", "2", "3", "4", "NULL"}},
                         {"CustomerName", {"NULL", "John", "David", "Emma", "NULL"}},
                         {"Age", {"NULL", "27", "35", "29", "NULL"}},
                         {"City", {"NULL", "Seattle", "New York", "Los Angeles", "NULL"}},
                     });
    EXPECT_EQ(result, expected);
}

TEST(DatabaseTests, INNER_JOIN) {
    request = R"(SELECT * FROM Customers
                JOIN Purchases ON PurchaseID = PurchaseID)";
    result = base.MakeRequest(request);
    expected = Table({
                         {"CustomerID", {"2", "3", "4"}},
                         {"CustomerName", {"John", "David", "Emma"}},
                         {"Age", {"27", "35", "29"}},
                         {"City", {"Seattle", "New York", "Los Angeles"}},
                         {"PurchaseID", {"202", "203", "204"}},
                         {"Product", {"Laptop", "Camera", "Headphones"}},
                         {"Price", {"1299", "699", "149"}}
                     });
    EXPECT_EQ(result, expected);
}

TEST(DatabaseTests, CREATE_TABLE) {
    request = R"(CREATE TABLE Shops (ShopName, City, ShopID, Rating) )";
    result = base.MakeRequest(request);
    expected = Table({
                         {"ShopName", {}},
                         {"City", {}},
                         {"ShopID", {}},
                         {"Rating", {}},
                     });
    EXPECT_EQ(result, expected);

    EXPECT_EQ(base.GetTables().count("Shops"), 1);
}

TEST(DatabaseTests, DROP_TABLE) {
    request = R"(DROP TABLE Shops)";
    base.MakeRequest(request);
    EXPECT_EQ(base.GetTables().count("Shops"), 0);
}

TEST(DatabaseTests, UPDATE) {
    request = R"(UPDATE Customers
                SET Age = 32, City = London
                WHERE CustomerName = Anna)";
    result = base.MakeRequest(request);
    expected = Table({
                         {"CustomerID", {"1", "2", "3", "4", "5"}},
                         {"CustomerName", {"Anna", "John", "David", "Emma", "Alex"}},
                         {"Age", {"32", "27", "35", "29", "33"}},
                         {"City", {"London", "Seattle", "New York", "Los Angeles", "Chicago"}},
                         {"PurchaseID", {"201", "202", "203", "204", "205"}},
                     });
    EXPECT_EQ(result, expected);

    request = R"(UPDATE Customers
                SET Age = 32, City = London
                WHERE Customer_Name = Anna)";
    EXPECT_THROW(base.MakeRequest(request), std::invalid_argument);
}

TEST(DatabaseTests, INSERT) {
    request = R"(CREATE TABLE Shops (ShopName, City, ShopID, Rating)
                 INSERT INTO Shops (ShopName, City, ShopID, Rating)
                 VALUES (Shop 1, New York, 123456, 4.5))";
    result = base.MakeRequest(request);
    expected = Table({
                         {"ShopName", {"Shop 1"}},
                         {"City", {"New York"}},
                         {"ShopID", {"123456"}},
                         {"Rating", {"4.5"}},
                     });
    EXPECT_EQ(result, expected);
}

TEST(DatabaseTests, DELETE) {
    request = R"(DELETE FROM Purchases
                 WHERE PurchaseID = 301 OR Product = Laptop)";
    result = base.MakeRequest(request);
    expected = Table({
                         {"PurchaseID", {"203", "204", "305"}},
                         {"Product", {"Camera", "Headphones", "Tablet"}},
                         {"Price", {"699", "149", "799"}}
                     });
    EXPECT_EQ(result, expected);
}

TEST(DatabaseTests, PRIMARY_KEY) {
    request = R"(CREATE TABLE Shops (ShopName, City, ShopID PRIMARY KEY, Rating) )";
    result = base.MakeRequest(request);
    EXPECT_EQ(result.GetPrimaryKey(), "ShopID");
}

TEST(DatabaseTests, FOREIGN_KEY) {
    request = R"(CREATE TABLE Purchases (PurchaseID, Product, Price, CustomerID)
                 FOREIGN KEY CustomerID REFERENCES Customers CustomerID)";
    result = base.MakeRequest(request);
    EXPECT_EQ(result.GetForeignKey().GetColumn1(), "CustomerID");
    EXPECT_EQ(result.GetForeignKey().GetColumn2(), "CustomerID");
    EXPECT_EQ(result.GetForeignKey().GetTable(), "Customers");
}
