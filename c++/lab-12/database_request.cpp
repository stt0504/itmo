#include "database.h"

void RemoveBlanks(std::string& str) {
    if (str.empty()) {
        return;
    }
    while (isblank(str[0])) {
        str.erase(0, 1);
    }
    while (isblank(str[str.size() - 1])) {
        str.erase(str.size() - 1, 1);
    }
}

void RemoveBrackets(std::string& str) {
    if (str.size() < 2) {
        return;
    }
    if (str[0] == '(') {
        str.erase(0, 1);
    }
    if (str[str.size() - 1] == ')') {
        str.erase(str.size() - 1, 1);
    }
}

std::vector<std::string> SplitBySymbol(const std::string& str, char del) {
    std::vector<std::string> result;
    std::string item;
    for (char ch : str) {
        if (ch == del) {
            RemoveBlanks(item);
            result.push_back(item);
            item.clear();
        } else {
            item += ch;

        }
    }
    if (!item.empty()) {
        RemoveBlanks(item);
        result.push_back(item);
    }
    return result;
}

std::vector<std::string> ParseString(std::string string) {
    std::vector<std::string> result;
    const std::vector<std::string> keywords =
        {"SELECT",
         "FROM",
         "WHERE",
         "LEFT JOIN",
         "RIGHT JOIN",
         "INNER JOIN",
         "JOIN",
         "CREATE TABLE",
         "DROP TABLE",
         "AND",
         "OR",
         "IS NOT",
         "IS",
         "NOT",
         "ON",
         ">=",
         "<=",
         ">",
         "<",
         "=",
         "!=",
         "UPDATE",
         "SET",
         "INSERT INTO",
         "VALUES",
         "DELETE FROM",
         "FOREIGN KEY",
         "REFERENCES"};

    RemoveBlanks(string);

    while (!string.empty()) {
        bool flag = false;
        size_t first_keyword = string.size();
        for (const auto& keyword : keywords) {
            if (string.find(keyword) == 0) {
                result.push_back(keyword);
                string = string.substr(keyword.length());
                RemoveBlanks(string);
                flag = true;
                break;
            } else if (string.find(keyword) != std::string::npos && string.find(keyword) < first_keyword) {
                first_keyword = string.find(keyword);
            }
        }
        if (!flag) {
            std::string args = string.substr(0, first_keyword);
            RemoveBlanks(args);
            result.push_back(args);
            string = string.substr(first_keyword);
            RemoveBlanks(string);
        }
    }
    return result;
}

bool IsInteger(const std::string& str) {
    std::istringstream iss(str);
    int num;
    iss >> std::noskipws >> num;
    return iss.eof() && !iss.fail();
}

bool IsFloat(const std::string& str) {
    std::istringstream iss(str);
    float num;
    iss >> std::noskipws >> num;
    return iss.eof() && !iss.fail();
}

bool IsDouble(const std::string& str) {
    std::istringstream iss(str);
    double num;
    iss >> std::noskipws >> num;
    return iss.eof() && !iss.fail();
}

bool IsBoolean(const std::string& str) {
    return str == "true" || str == "false";
}

int CompareStrings(const std::string& str1, const std::string& str2) {
    if (IsInteger(str1) && IsInteger(str2)) {
        int num1 = stoi(str1);
        int num2 = stoi(str2);
        return num1 - num2;
    } else if (IsFloat(str1) && IsFloat(str2)) {
        float num1 = stof(str1);
        float num2 = stof(str2);
        if (num1 < num2) {
            return -1;
        }
        if (num1 > num2) {
            return 1;
        }
        return 0;
    } else if (IsDouble(str1) && IsDouble(str2)) {
        double num1 = stod(str1);
        double num2 = stod(str2);
        if (num1 < num2) {
            return -1;
        }
        if (num1 > num2) {
            return 1;
        }
        return 0;
    } else if (IsBoolean(str1) && IsBoolean(str2)) {
        int bool1 = str1 == "true" ? 1 : 0;
        int bool2 = str2 == "true" ? 1 : 0;
        return bool1 - bool2;
    } else {
        return str1.compare(str2);
    }
}

void Database::DatabaseRequest::ParseRequest() {
    std::vector<std::string> lines = SplitBySymbol(request, '\n');
    for (int i = 0; i < lines.size(); i++) {
        std::vector<std::string> line = ParseString(lines[i]);
        parsed_data.push_back(line);
    }
}

const std::vector<std::vector<std::string>>& Database::DatabaseRequest::GetParsedData() const {
    return parsed_data;
}

void Database::DatabaseRequest::SELECT_FROM(const std::string& table_name,
                                            const std::vector<std::string>& columns_names) {
    std::unordered_map<std::string, std::vector<std::string>> requested_data;
    for (const auto& table : database.tables) {
        if (table.first == table_name) {
            if (database.tables.count(table_name) == 0) {
                throw std::invalid_argument("SELECT_FROM");
            }
            auto& selected_table = database.tables.at(table_name);
            for (const auto& column : columns_names) {
                if (selected_table.GetData().count(column) == 0) {
                    throw std::invalid_argument("SELECT_FROM");
                }
                requested_data.emplace(column, selected_table.GetData().at(column));
            }
        }
    }
    requested_table = Table(requested_data);
}

void Database::DatabaseRequest::WHERE(const std::function<bool(int)>& func) {
    std::unordered_map<std::string, std::vector<std::string>> old_data = requested_table.GetData();
    std::unordered_map<std::string, std::vector<std::string>> new_data;

    for (const auto& pair : old_data) {
        const std::string& key = pair.first;
        std::vector<std::string> new_vector;
        new_data[key] = new_vector;
    }

    for (int i = 0; i < old_data.begin()->second.size(); i++) {
        if (func(i)) {
            for (auto& it : old_data) {
                new_data[it.first].push_back(it.second[i]);
            }
        }
    }
    requested_table = Table(new_data);
}

void Database::DatabaseRequest::CREATE_TABLE(const std::string& table_name,
                                             const std::vector<std::string>& columns_names) {
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::string pk;
    for (std::string columns_name : columns_names) {
        size_t index = columns_name.find("PRIMARY KEY");
        if (index != std::string::npos) {
            columns_name = columns_name.substr(0, index);
            RemoveBlanks(columns_name);
            pk = columns_name;
        }
        data.emplace(columns_name, std::vector<std::string>());
    }
    Table table(data);
    table.SetPrimaryKey(pk);
    database.AddTable(table_name, table);
    requested_table = table;
}

void Database::DatabaseRequest::DROP_TABLE(const std::string& table_name) {
    database.DeleteTable(table_name);
}

void Database::DatabaseRequest::SET_WHERE(const std::unordered_map<std::string, std::string>& columns_and_values,
                                          const std::function<bool(int)>& condition, const std::string& table_name) {
    if (database.tables.count(table_name) == 0) {
        throw std::invalid_argument("SET_WHERE");
    }
    std::unordered_map<std::string, std::vector<std::string>> data = database.tables.at(table_name).GetData();
    requested_table = Table(data);
    for (int j = 0; j < data.begin()->second.size(); j++) {
        if (condition(j)) {
            for (const auto& column_and_value : columns_and_values) {
                requested_table.SetValue(column_and_value.first, j, column_and_value.second);
            }
        }
    }
}

void Database::DatabaseRequest::INSERT_INTO(const std::unordered_map<std::string, std::string>& columns_and_values,
                                            const std::string& table_name) {
    if (database.tables.count(table_name) == 0) {
        throw std::invalid_argument("SET_WHERE");
    }
    std::unordered_map<std::string, std::vector<std::string>> data = database.tables.at(table_name).GetData();
    for (auto& it : data) {
        if (columns_and_values.count(it.first)) {
            it.second.push_back(columns_and_values.at(it.first));
        } else {
            it.second.emplace_back("NULL");
        }
    }
    requested_table = Table(data);
}

void Database::DatabaseRequest::DELETE_WHERE(const std::function<bool(int)>& condition, const std::string& table_name) {
    if (database.tables.count(table_name) == 0) {
        throw std::invalid_argument("DELETE_WHERE");
    }
    std::unordered_map<std::string, std::vector<std::string>> data = database.tables.at(table_name).GetData();
    for (int i = data.begin()->second.size() - 1; i >= 0; i--) {
        if (condition(i)) {
            for (auto& it : data) {
                it.second.erase(it.second.begin() + i);
            }
        }
    }
    requested_table = Table(data);
}

void Database::DatabaseRequest::JOIN(const std::string& table_name_1,
                                     const std::string& table_name_2,
                                     const std::string& column1,
                                     const std::string& column2) {
    if (database.tables.count(table_name_1) == 0) {
        throw std::invalid_argument("JOIN");
    }
    if (database.tables.count(table_name_2) == 0) {
        throw std::invalid_argument("JOIN");
    }
    std::unordered_map<std::string, std::vector<std::string>> table1 = database.tables[table_name_1].GetData();
    std::unordered_map<std::string, std::vector<std::string>> table2 = database.tables[table_name_2].GetData();

    if (table1.count(column1) == 0) {
        throw std::invalid_argument("JOIN");
    }
    if (table2.count(column2) == 0) {
        throw std::invalid_argument("JOIN");
    }
    std::vector<std::string>& column1Values = table1[column1];
    std::vector<std::string>& column2Values = table2[column2];

    std::unordered_map<std::string, std::vector<std::string>> joinedTable = table1;
    for (auto it = table2.begin(); it != table2.end(); it++) {
        joinedTable.emplace(it->first, std::vector<std::string>(it->second.size()));
    }
    std::vector<int> empty_index;

    for (int i = 0; i < column1Values.size(); i++) {
        const std::string& value = column1Values[i];
        auto it = std::find(column2Values.begin(), column2Values.end(), value);
        size_t index = std::distance(column2Values.begin(), it);
        if (index != column2Values.size()) {
            for (auto it = table2.begin(); it != table2.end(); it++) {
                joinedTable[it->first][i] = table2[it->first][index];
            }
        } else {
            empty_index.emplace_back(i);
        }
    }

    for (int i = empty_index.size() - 1; i >= 0; i--) {
        for (auto it = joinedTable.begin(); it != joinedTable.end(); it++) {
            it->second.erase(it->second.begin() + empty_index[i]);
        }
    }

    requested_table = Table(joinedTable);

}

void Database::DatabaseRequest::LEFT_JOIN(const std::string& table_name_1,
                                          const std::string& table_name_2,
                                          const std::string& column1,
                                          const std::string& column2) {
    if (database.tables.count(table_name_1) == 0) {
        throw std::invalid_argument("JOIN");
    }
    if (database.tables.count(table_name_2) == 0) {
        throw std::invalid_argument("JOIN");
    }
    std::unordered_map<std::string, std::vector<std::string>> table1 = database.tables[table_name_1].GetData();
    std::unordered_map<std::string, std::vector<std::string>> table2 = database.tables[table_name_2].GetData();

    if (table1.count(column1) == 0) {
        throw std::invalid_argument("JOIN");
    }
    if (table2.count(column2) == 0) {
        throw std::invalid_argument("JOIN");
    }

    std::vector<std::string>& column1Values = table1[column1];
    std::vector<std::string>& column2Values = table2[column2];

    std::unordered_map<std::string, std::vector<std::string>> joinedTable = table1;
    for (auto it = table2.begin(); it != table2.end(); it++) {
        joinedTable.emplace(it->first, std::vector<std::string>(it->second.size()));
    }
    std::vector<int> empty_index;

    for (int i = 0; i < column1Values.size(); i++) {
        const std::string& value = column1Values[i];
        auto it = std::find(column2Values.begin(), column2Values.end(), value);
        size_t index = std::distance(column2Values.begin(), it);
        if (index != column2Values.size()) {
            for (auto it = table2.begin(); it != table2.end(); it++) {
                joinedTable[it->first][i] = table2[it->first][index];
            }
        } else {
            for (auto it = table2.begin(); it != table2.end(); it++) {
                if (it->first != column1) {
                    joinedTable[it->first][i] = "NULL";
                }
            }
        }
    }
    requested_table = Table(joinedTable);
}

void Database::DatabaseRequest::FOREIGN_KEY(const std::string& table_name,
                                            const std::string& column1,
                                            const std::string& column2) {
    requested_table.foreign_key = Table::ForeignKey(table_name, column1, column2);
}

std::function<bool(int i)> ParseFunction(std::vector<std::string>& condition,
                                         const std::unordered_map<std::string, std::vector<std::string>>& data) {
    std::vector<std::function<bool(int i)>> condition_func_vec;
    int k = -1;
    for (int i = 0; i < condition.size(); i++) {
        if (condition[i] == "IS NOT" || condition[i] == "!=") {
            if (i == 0 || i == condition.size() - 1) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            std::string column = condition[i - 1];
            std::string value = condition[i + 1];
            std::function<bool(int i)>
                f = [&data, column, value](int i) {
                if (data.count(column) == 0) {
                    throw std::invalid_argument("WHERE");
                }
                if (i >= data.at(column).size()) {
                    throw std::invalid_argument("WHERE");
                }
                return CompareStrings(data.at(column)[i], value) != 0;
            };
            condition_func_vec.push_back(f);
            k++;
            condition.erase(condition.begin() + i - 1, condition.begin() + i + 2);
            condition.insert(condition.begin() + i - 1, std::to_string(k));
        } else if (condition[i] == "IS" || condition[i] == "=") {
            if (i == 0 || i == condition.size() - 1) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            std::string column = condition[i - 1];
            std::string value = condition[i + 1];
            std::function<bool(int i)>
                f = [&data, column, value](int i) {
                if (data.count(column) == 0) {
                    throw std::invalid_argument("WHERE");
                }
                if (i >= data.at(column).size()) {
                    std::cout << "!" << std::endl;
                    throw std::invalid_argument("WHERE");
                }
                return CompareStrings(data.at(column)[i], value) == 0;
            };
            condition_func_vec.push_back(f);
            k++;
            condition.erase(condition.begin() + i - 1, condition.begin() + i + 2);
            condition.insert(condition.begin() + i - 1, std::to_string(k));
        } else if (condition[i] == ">") {
            if (i == 0 || i == condition.size() - 1) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            std::string column = condition[i - 1];
            std::string value = condition[i + 1];
            std::function<bool(int i)>
                f = [&data, column, value](int i) {
                if (data.count(column) == 0) {
                    throw std::invalid_argument("WHERE");
                }
                if (i >= data.at(column).size()) {
                    throw std::invalid_argument("WHERE");
                }
                return CompareStrings(data.at(column)[i], value) > 0;
            };
            condition_func_vec.push_back(f);
            k++;
            condition.erase(condition.begin() + i - 1, condition.begin() + i + 2);
            condition.insert(condition.begin() + i - 1, std::to_string(k));
        } else if (condition[i] == "<") {
            if (i == 0 || i == condition.size() - 1) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            std::string column = condition[i - 1];
            std::string value = condition[i + 1];
            std::function<bool(int i)>
                f = [&data, column, value](int i) {
                if (data.count(column) == 0) {
                    throw std::invalid_argument("WHERE");
                }
                if (i >= data.at(column).size()) {
                    throw std::invalid_argument("WHERE");
                }
                return CompareStrings(data.at(column)[i], value) < 0;
            };
            condition_func_vec.push_back(f);
            k++;
            condition.erase(condition.begin() + i - 1, condition.begin() + i + 2);
            condition.insert(condition.begin() + i - 1, std::to_string(k));
        } else if (condition[i] == ">=") {
            if (i == 0 || i == condition.size() - 1) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            std::string column = condition[i - 1];
            std::string value = condition[i + 1];
            std::function<bool(int i)>
                f = [&data, column, value](int i) {
                if (data.count(column) == 0) {
                    throw std::invalid_argument("WHERE");
                }
                if (i >= data.at(column).size()) {
                    throw std::invalid_argument("WHERE");
                }
                return CompareStrings(data.at(column)[i], value) >= 0;
            };
            condition_func_vec.push_back(f);
            k++;
            condition.erase(condition.begin() + i - 1, condition.begin() + i + 2);
            condition.insert(condition.begin() + i - 1, std::to_string(k));
        } else if (condition[i] == "<=") {
            if (i == 0 || i == condition.size() - 1) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            std::string column = condition[i - 1];
            std::string value = condition[i + 1];
            std::function<bool(int i)>
                f = [&data, column, value](int i) {
                if (data.count(column) == 0) {
                    throw std::invalid_argument("WHERE");
                }
                if (i >= data.at(column).size()) {
                    throw std::invalid_argument("WHERE");
                }
                return CompareStrings(data.at(column)[i], value) <= 0;
            };
            condition_func_vec.push_back(f);
            k++;
            condition.erase(condition.begin() + i - 1, condition.begin() + i + 2);
            condition.insert(condition.begin() + i - 1, std::to_string(k));
        }
    }
    int i = 0;
    while (condition.size() != 1) {
        if (condition[i] == "AND") {
            if (i == 0 || i == condition.size() - 1) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            int number_function_1 = stoi(condition[i - 1]);
            int number_function_2 = stoi(condition[i + 1]);
            if (number_function_1 >= condition_func_vec.size()) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            if (number_function_2 >= condition_func_vec.size()) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            std::function f1 = condition_func_vec[number_function_1];
            std::function f2 = condition_func_vec[number_function_2];
            std::function<bool(int i)> f = [f1, f2](int i) {
                return f1(i) && f2(i);
            };
            condition_func_vec.push_back(f);
            k++;
            condition.erase(condition.begin() + i - 1, condition.begin() + i + 2);
            condition.insert(condition.begin() + i - 1, std::to_string(k));
            i++;
            if (i == condition.size()) {
                i = 0;
            }
        } else if (condition[i] == "OR") {
            if (i == 0 || i == condition.size() - 1) {
                throw std::invalid_argument("WHERE: invalid condition");
            }
            int number_function_1 = stoi(condition[i - 1]);
            int number_function_2 = stoi(condition[i + 1]);
            std::function f1 = condition_func_vec[number_function_1];
            std::function f2 = condition_func_vec[number_function_2];
            std::function<bool(int i)> f = [f1, f2](int i) {
                return f1(i) || f2(i);
            };
            condition_func_vec.push_back(f);
            k++;
            condition.erase(condition.begin() + i - 1, condition.begin() + i + 2);
            condition.insert(condition.begin() + i - 1, std::to_string(k));
            i++;
            if (i == condition.size()) {
                i = 0;
            }
        } else {
            i++;
            if (i == condition.size()) {
                i = 0;
            }
        }
    }
    if (!IsInteger(condition[0]) || stoi(condition[0]) >= condition_func_vec.size()) {
        throw std::invalid_argument("WHERE: invalid condition");
    }
    return condition_func_vec[stoi(condition[0])];
}
