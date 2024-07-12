#pragma once
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Table {
    private:
        class ForeignKey {
            private:
                std::string table;
                std::string column1;
                std::string column2;
            public:
                ForeignKey() = default;

                ForeignKey(const std::string& table, const std::string& column1, const std::string& column2) : table(
                    table), column1(column1), column2(column2) {}

                const std::string& GetTable() const;

                const std::string& GetColumn1() const;

                const std::string& GetColumn2() const;
        };

        void SetValue(const std::string& column_name, int string_number, const std::string& value);

        void SetPrimaryKey(const std::string& pk);

        std::string primary_key;
        ForeignKey foreign_key;
        std::unordered_map<std::string, std::vector<std::string>> data;
    public:
        friend class Database;

        Table() = default;

        explicit Table(const std::unordered_map<std::string, std::vector<std::string>>& data) : data(data) {};

        const std::unordered_map<std::string, std::vector<std::string>>& GetData() const;

        const std::string& GetPrimaryKey() const;

        const ForeignKey& GetForeignKey() const;

        friend std::ostream& operator<<(std::ostream& os, const Table& table);
};

bool operator==(const Table& lhs, const Table& rhs);

bool operator!=(const Table& lhs, const Table& rhs);

class Database {
    private:
        void AddTable(const std::string& table_name, const Table& table);

        void DeleteTable(const std::string& table_name);

        class DatabaseRequest {
            private:
                Database& database;
                std::string request;
                Table requested_table;
                std::vector<std::vector<std::string>> parsed_data;
            public:
                DatabaseRequest(Database& database, const std::string& request)
                    : database(database), request(request) {}

                void ParseRequest();

                void SELECT_FROM(const std::string& table_name, const std::vector<std::string>& columns_names);

                void WHERE(const std::function<bool(int i)>& func);

                void CREATE_TABLE(const std::string& table_name, const std::vector<std::string>& columns_names);

                void DROP_TABLE(const std::string& table_name);

                void SET_WHERE(const std::unordered_map<std::string, std::string>& columns_and_values,
                               const std::function<bool(int i)>& condition,
                               const std::string& table_name);

                void DELETE_WHERE(const std::function<bool(int i)>& condition,
                                  const std::string& table_name);

                void INSERT_INTO(const std::unordered_map<std::string, std::string>& columns_and_values,
                                 const std::string& table_name);

                void JOIN(const std::string& table_name_1,
                          const std::string& table_name_2,
                          const std::string& column1,
                          const std::string& column2);

                void LEFT_JOIN(const std::string& table_name_1,
                               const std::string& table_name_2,
                               const std::string& column1,
                               const std::string& column2);

                void FOREIGN_KEY(const std::string& table_name,
                                 const std::string& column1,
                                 const std::string& column2);

                const std::vector<std::vector<std::string>>& GetParsedData() const;

                const Table& GetRequestedTable() const {
                    return requested_table;
                }
        };

        std::optional<DatabaseRequest> request;
        std::unordered_map<std::string, Table> tables;
    public:
        explicit Database(const std::unordered_map<std::string, Table>& tables) : tables(tables) {};

        Table MakeRequest(const std::string& request_str);

        const std::unordered_map<std::string, Table>& GetTables() const;
};

std::vector<std::string> SplitBySymbol(const std::string& str, char del);

int CompareStrings(const std::string& str1, const std::string& str2);

void RemoveBrackets(std::string& str);

std::function<bool(int i)> ParseFunction(std::vector<std::string>& condition,
                                         const std::unordered_map<std::string, std::vector<std::string>>& data);
