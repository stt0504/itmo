using System.Collections.ObjectModel;
using Lab05.Models;
using Npgsql;

namespace Lab05.Entities.DatabaseManager;

public class DatabaseManager : IDataManager
{
    private readonly string _connectionString;

    public DatabaseManager(string connectionString)
    {
        _connectionString = connectionString;
    }

    public async Task<Account?> GetAccount(int accountNumber)
    {
        const string request = @"
                       SELECT accountnumber, pin, balance
                       FROM accounts
                       WHERE accountnumber = @accountNumber;
                       ";

        using var connection = new NpgsqlConnection(_connectionString);
        await connection.OpenAsync().ConfigureAwait(false);

        using var command = new NpgsqlCommand(request, connection);
        command.Parameters.AddWithValue("accountNumber", accountNumber);

        using NpgsqlDataReader reader = await command.ExecuteReaderAsync().ConfigureAwait(false);
        if (await reader.ReadAsync().ConfigureAwait(false) is false) return null;

        return new Account(reader.GetInt32(0), reader.GetInt32(1), reader.GetInt32(2), await GetOperationHistory(reader.GetInt32(0)).ConfigureAwait(false));
    }

    public async void UpdateBalance(int accountNumber, int value)
    {
        const string request = @"
                           UPDATE accounts
                           SET balance = @value
                           WHERE accountnumber = @accountNumber;
                       ";

        using var connection = new NpgsqlConnection(_connectionString);
        await connection.OpenAsync().ConfigureAwait(false);

        using var command = new NpgsqlCommand(request, connection);
        command.Parameters.AddWithValue("value", value);
        command.Parameters.AddWithValue("accountNumber", accountNumber);

        await command.ExecuteNonQueryAsync().ConfigureAwait(false);
    }

    public async void AddAccount(int accountNumber, int pin)
    {
        const string request = @"
                           INSERT INTO accounts (accountnumber, pin, balance)
                           VALUES (@accountNumber, @pin, 0);
                       ";

        using var connection = new NpgsqlConnection(_connectionString);
        await connection.OpenAsync().ConfigureAwait(false);

        using var command = new NpgsqlCommand(request, connection);
        command.Parameters.AddWithValue("accountNumber", accountNumber);
        command.Parameters.AddWithValue("pin", pin);

        await command.ExecuteNonQueryAsync().ConfigureAwait(false);
    }

    public async void AddOperation(int accountNumber, string operationType, int amount, string operationDate, string operationTime)
    {
        const string request = @"
                           INSERT INTO operations (accountnumber, operationtype, amount, operationdate, operationtime)
                           VALUES (@accountNumber, @operationType, @amount, @operationDate, @operationTime);
                       ";

        using var connection = new NpgsqlConnection(_connectionString);
        await connection.OpenAsync().ConfigureAwait(false);

        using var command = new NpgsqlCommand(request, connection);
        command.Parameters.AddWithValue("accountNumber", accountNumber);
        command.Parameters.AddWithValue("operationType", operationType);
        command.Parameters.AddWithValue("amount", amount);
        command.Parameters.AddWithValue("operationDate", operationDate);
        command.Parameters.AddWithValue("operationTime", operationTime);

        await command.ExecuteNonQueryAsync().ConfigureAwait(false);
    }

    private async Task<Collection<Operation>> GetOperationHistory(int accountNumber)
    {
        const string request = @"
                           SELECT accountnumber, operationtype, amount, operationDate, operationTime
                           FROM operations
                           WHERE accountnumber = @accountNumber;
                       ";

        using var connection = new NpgsqlConnection(_connectionString);
        await connection.OpenAsync().ConfigureAwait(false);

        using var command = new NpgsqlCommand(request, connection);
        command.Parameters.AddWithValue("accountNumber", accountNumber);

        using NpgsqlDataReader reader = await command.ExecuteReaderAsync().ConfigureAwait(false);

        var operations = new Collection<Operation>();
        while (await reader.ReadAsync().ConfigureAwait(false))
        {
            var operation = new Operation(reader.GetInt32(0), reader.GetString(1), reader.GetInt32(2), reader.GetString(3), reader.GetString(4));
            operations.Add(operation);
        }

        return operations;
    }
}