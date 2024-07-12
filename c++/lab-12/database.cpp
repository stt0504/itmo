#include "database.h"

const std::unordered_map<std::string, Table>& Database::GetTables() const {
    return tables;
}

void Database::AddTable(const std::string& table_name, const Table& table) {
    tables.emplace(table_name, table);
}

void Database::DeleteTable(const std::string& table_name) {
    tables.erase(table_name);
}

Table Database::MakeRequest(const std::string& request_str) {
    request.emplace(*this, request_str);
    request->ParseRequest();
    const std::vector<std::vector<std::string>>& parsed_data = request->GetParsedData();
    std::string table_name;
    std::vector<std::string> columns;
    for (size_t line_index = 0; line_index < parsed_data.size(); line_index++) {
        if (parsed_data[line_index].empty() || parsed_data[line_index][0] == "WHERE") {
            continue;
        } else if (parsed_data[line_index][0] == "SELECT") {
            const int select_size = 4;
            if (parsed_data[line_index].size() < select_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int columns_index = 1;
            std::string columns_str = parsed_data[line_index][columns_index];
            const int table_name_index = 3;
            table_name = parsed_data[line_index][table_name_index];
            if (columns_str != "*") {
                columns = SplitBySymbol(columns_str, ',');
            } else {
                if (tables.count(table_name) == 0) {
                    throw std::invalid_argument("No such table: " + table_name);
                }
                for (const auto& column : tables.at(table_name).GetData()) {
                    columns.push_back(column.first);
                }
            }
            request->SELECT_FROM(table_name, columns);
            line_index++;
            if (parsed_data.size() > line_index && !parsed_data[line_index].empty()
                && parsed_data[line_index][0] == "WHERE") {
                if (tables.count(table_name) == 0) {
                    throw std::invalid_argument("No such table: " + table_name);
                }
                const auto& data = tables.at(table_name).GetData();
                std::vector<std::string>
                    condition_vec = std::vector<std::string>(parsed_data[line_index].begin() + 1,
                                                             parsed_data[line_index].end());
                request->WHERE(ParseFunction(condition_vec, data));
            } else {
                line_index--;
            }
        } else if (parsed_data[line_index][0] == "CREATE TABLE") {
            const int create_table_size = 2;
            if (parsed_data[line_index].size() < create_table_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int data_index = 1;
            size_t space_index = parsed_data[line_index][data_index].find(' ');
            table_name = parsed_data[line_index][data_index].substr(0, space_index);
            std::string columns_str = parsed_data[line_index][data_index].substr(space_index + 1);
            RemoveBrackets(columns_str);
            columns = SplitBySymbol(columns_str, ',');
            request->CREATE_TABLE(table_name, columns);
        } else if (parsed_data[line_index][0] == "DROP TABLE") {
            const int drop_table_size = 2;
            if (parsed_data[line_index].size() < drop_table_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int table_name_index = 1;
            table_name = parsed_data[line_index][table_name_index];
            request->DROP_TABLE(table_name);
        } else if (parsed_data[line_index][0] == "UPDATE") {
            const int update_size = 2;
            if (parsed_data[line_index].size() < update_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int table_name_index = 1;
            table_name = parsed_data[line_index][table_name_index];
        } else if (parsed_data[line_index][0] == "SET") {
            std::vector<std::string>
                actions = std::vector<std::string>(parsed_data[line_index].begin() + 1, parsed_data[line_index].end());
            for (int i = 0; i < actions.size(); i++) {
                if (actions[i] == "=") {
                    actions.erase(actions.begin() + i);
                }
                if (actions[i].find(',') != std::string::npos) {
                    auto pair = SplitBySymbol(actions[i], ',');
                    actions.erase(actions.begin() + i);
                    actions.insert(actions.begin() + i, pair.begin(), pair.end());
                    i++;
                }
            }
            std::unordered_map<std::string, std::string> columns_and_values;
            for (int i = 0; i < actions.size(); i += 2) {
                if (i + 1 >= actions.size()) {
                    throw std::invalid_argument("SET");
                }
                columns_and_values.emplace(actions[i], actions[i + 1]);
            }
            if (tables.count(table_name) == 0) {
                throw std::invalid_argument("No such table: " + table_name);
            }
            const auto& data = tables[table_name].GetData();
            line_index++;
            if (parsed_data.size() > line_index && !parsed_data[line_index].empty()
                && parsed_data[line_index][0] == "WHERE") {
                std::vector<std::string>
                    condition_vec =
                    std::vector<std::string>(parsed_data[line_index].begin() + 1, parsed_data[line_index].end());
                std::function<bool(int i)> condition = ParseFunction(condition_vec, data);
                request->SET_WHERE(columns_and_values, condition, table_name);
            } else {
                throw std::invalid_argument("Invalid request");
            }
        } else if (parsed_data[line_index][0] == "INSERT INTO") {
            const int insert_size = 2;
            if (parsed_data[line_index].size() < insert_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int data_index = 1;
            size_t space_index = parsed_data[line_index][data_index].find(' ');
            table_name = parsed_data[line_index][data_index].substr(0, space_index);
            std::string columns_str = parsed_data[line_index][data_index].substr(space_index + 1);
            RemoveBrackets(columns_str);
            columns = SplitBySymbol(columns_str, ',');
        } else if (parsed_data[line_index][0] == "VALUES") {
            const int values_size = 2;
            if (parsed_data[line_index].size() < values_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int values_string_index = 1;
            std::string values_string = parsed_data[line_index][values_string_index];
            RemoveBrackets(values_string);
            auto values = SplitBySymbol(values_string, ',');
            std::unordered_map<std::string, std::string> columns_and_values;
            for (int i = 0; i < columns.size(); i++) {
                columns_and_values.emplace(columns[i], values[i]);
            }
            request->INSERT_INTO(columns_and_values, table_name);
        } else if (parsed_data[line_index][0] == "DELETE FROM") {
            const int delete_size = 2;
            if (parsed_data[line_index].size() < delete_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int table_name_index = 1;
            table_name = parsed_data[line_index][table_name_index];
            if (tables.count(table_name) == 0) {
                throw std::invalid_argument("No such table: " + table_name);
            }
            const auto& data = tables.at(table_name).GetData();
            line_index++;
            if (parsed_data.size() > line_index && !parsed_data[line_index].empty()
                && parsed_data[line_index][0] == "WHERE") {
                std::vector<std::string>
                    condition_vec =
                    std::vector<std::string>(parsed_data[line_index].begin() + 1, parsed_data[line_index].end());
                std::function<bool(int i)> condition = ParseFunction(condition_vec, data);
                request->DELETE_WHERE(condition, table_name);
            } else {
                throw std::invalid_argument("Invalid request");
            }
        } else if (parsed_data[line_index][0] == "JOIN" || parsed_data[line_index][0] == "INNER JOIN") {
            const int join_size = 6;
            if (parsed_data[line_index].size() < join_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int table_name_2_index = 1;
            std::string table_name_2 = parsed_data[line_index][table_name_2_index];
            const int column1_index = 3;
            std::string column1 = parsed_data[line_index][column1_index];
            const int column2_index = 5;
            std::string column2 = parsed_data[line_index][column2_index];
            request->JOIN(table_name, table_name_2, column1, column2);
        } else if (parsed_data[line_index][0] == "LEFT JOIN") {
            const int join_size = 6;
            if (parsed_data[line_index].size() < join_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int table_name_2_index = 1;
            std::string table_name_2 = parsed_data[line_index][table_name_2_index];
            const int column1_index = 3;
            std::string column1 = parsed_data[line_index][column1_index];
            const int column2_index = 5;
            std::string column2 = parsed_data[line_index][column2_index];
            request->LEFT_JOIN(table_name, table_name_2, column1, column2);
        } else if (parsed_data[line_index][0] == "RIGHT JOIN") {
            const int join_size = 6;
            if (parsed_data[line_index].size() < join_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int table_name_2_index = 1;
            std::string table_name_2 = parsed_data[line_index][table_name_2_index];
            const int column1_index = 3;
            std::string column1 = parsed_data[line_index][column1_index];
            const int column2_index = 5;
            std::string column2 = parsed_data[line_index][column2_index];
            request->LEFT_JOIN(table_name_2, table_name, column1, column2);
        } else if (parsed_data[line_index][0] == "FOREIGN KEY") {
            const int foreign_key_size = 4;
            if (parsed_data[line_index].size() < foreign_key_size) {
                throw std::invalid_argument("Invalid request");
            }
            const int column1_index = 1;
            std::string column1 = parsed_data[line_index][column1_index];
            const int data_index = 3;
            std::vector<std::string> data = SplitBySymbol(parsed_data[line_index][data_index], ' ');
            const int data_size = 2;
            if (data.size() < data_size) {
                throw std::invalid_argument("Invalid request");
            }
            std::string table_name_2 = data[0];
            std::string column2 = data[1];
            request->FOREIGN_KEY(table_name_2, column1, column2);
        } else {
            throw std::invalid_argument("Invalid request");
        }
    }
    return request->GetRequestedTable();
}

const std::unordered_map<std::string, std::vector<std::string>>& Table::GetData() const {
    return data;
}

std::ostream& operator<<(std::ostream& os, const Table& table) {
    if (table.data.empty()) {
        return os;
    }

    int col_width = 0;
    for (const auto& pair : table.data) {
        for (const auto& value : pair.second) {
            col_width = std::max(col_width, static_cast<int>(value.size()));
        }
        col_width = std::max(col_width, static_cast<int>(pair.first.size()));
    }
    col_width += 2;

    os << std::left << std::setw(col_width) << "Value";
    for (const auto& pair : table.data) {
        os << std::left << std::setw(col_width) << pair.first;
    }
    os << std::endl;

    for (size_t i = 0; i < table.data.begin()->second.size(); i++) {
        os << std::left << std::setw(col_width) << "Row " + std::to_string(i + 1);
        for (const auto& pair : table.data) {
            os << std::left << std::setw(col_width) << pair.second[i];
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

void Table::SetValue(const std::string& column_name, int string_number, const std::string& value) {
    if (data.count(column_name) == 0) {
        throw std::invalid_argument("No such column: " + column_name);
    }
    if (string_number >= data[column_name].size()) {
        throw std::invalid_argument("No such element with index: " + std::to_string(string_number));
    }
    data[column_name][string_number] = value;
}

void Table::SetPrimaryKey(const std::string& pk) {
    primary_key = pk;
}

const std::string& Table::GetPrimaryKey() const {
    return primary_key;
}

const Table::ForeignKey& Table::GetForeignKey() const {
    return foreign_key;
}

bool operator==(const Table& lhs, const Table& rhs) {
    return lhs.GetData() == rhs.GetData();
}

bool operator!=(const Table& lhs, const Table& rhs) {
    return !(lhs == rhs);
}

const std::string& Table::ForeignKey::GetTable() const {
    return table;
}

const std::string& Table::ForeignKey::GetColumn1() const {
    return column1;
}

const std::string& Table::ForeignKey::GetColumn2() const {
    return column2;
}
