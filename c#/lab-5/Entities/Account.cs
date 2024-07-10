using System.Collections.ObjectModel;
using System.Globalization;
using Lab05.Models;

namespace Lab05.Entities;

public class Account
{
    public Account(int accountNumber, int pin)
    {
        AccountNumber = accountNumber;
        Pin = pin;
        Balance = 0;
        Operations = new Collection<Operation>();
    }

    public Account(int accountNumber, int pin, int balance, Collection<Operation> operations)
    {
        AccountNumber = accountNumber;
        Pin = pin;
        Balance = balance;
        Operations = operations;
    }

    public int AccountNumber { get; }
    public int Pin { get; }
    public int Balance { get; private set; }
    public Collection<Operation> Operations { get; }

    public void Withdraw(int amount)
    {
        if (amount <= 0)
        {
            throw new ArgumentException("Cannot withdraw negative number");
        }

        if (amount > Balance)
        {
            throw new ArgumentException("Balance is not enough");
        }

        Balance -= amount;
        Operations.Add(new Operation(AccountNumber, "withdraw", amount, DateTime.Now.ToString("dd.MM.yyyy", new DateTimeFormatInfo()), DateTime.Now.ToString("HH:mm:ss", new DateTimeFormatInfo())));
    }

    public void Deposit(int amount)
    {
        if (amount <= 0)
        {
            throw new ArgumentException("Cannot deposit negative number");
        }

        Balance += amount;
        Operations.Add(new Operation(AccountNumber, "deposit", amount, DateTime.Now.ToString("dd.MM.yyyy", new DateTimeFormatInfo()), DateTime.Now.ToString("HH:mm:ss", new DateTimeFormatInfo())));
    }
}