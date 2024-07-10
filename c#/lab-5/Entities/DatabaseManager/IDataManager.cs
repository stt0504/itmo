namespace Lab05.Entities.DatabaseManager;

public interface IDataManager
{
    public Task<Account?> GetAccount(int accountNumber);
    public void UpdateBalance(int accountNumber, int value);
    public void AddAccount(int accountNumber, int pin);
    public void AddOperation(int accountNumber, string operationType, int amount, string operationDate, string operationTime);
}