namespace Lab05.Models;

public class Operation
{
    public Operation(int accountNumber, string operationType, int amount, string date, string time)
    {
        AccountNumber = accountNumber;
        OperationType = operationType;
        Amount = amount;
        Date = date;
        Time = time;
    }

    public int AccountNumber { get; }
    public string OperationType { get; }
    public int Amount { get; }
    public string Date { get; }
    public string Time { get; }
}