using System.Collections.ObjectModel;
using System.Globalization;
using Lab05.Entities;
using Lab05.Entities.DatabaseManager;
using Lab05.Models;

namespace Lab05.Services;

public class UserService : IUserService
{
    private readonly IDataManager _manager;
    private Account? _currentAccount;

    public UserService(IDataManager manager)
    {
        _manager = manager;
    }

    public void CreateAccount(int accountNumber, int pin)
    {
        _manager.AddAccount(accountNumber, pin);
    }

    public void Login(int accountNumber, int pin)
    {
        Account? account = _manager.GetAccount(accountNumber).Result;
        if (account is null) throw new ArgumentException("result is null");

        if (account.Pin != pin)
        {
            throw new ArgumentException("Incorrect PIN");
        }

        _currentAccount = account;
    }

    public void Deposit(int amount)
    {
        if (_currentAccount is null) throw new ArgumentException("current account is null");
        _currentAccount.Deposit(amount);
        _manager.UpdateBalance(_currentAccount.AccountNumber, _currentAccount.Balance);
        _manager.AddOperation(_currentAccount.AccountNumber, "deposit", amount, DateTime.Today.ToString("yyyy-MM-dd", new NumberFormatInfo()), DateTime.Now.ToString("HH:mm:ss", new NumberFormatInfo()));
    }

    public void Withdraw(int amount)
    {
        if (_currentAccount is null) throw new ArgumentException("current account is null");
        _currentAccount.Withdraw(amount);
        _manager.UpdateBalance(_currentAccount.AccountNumber, _currentAccount.Balance);
        _manager.AddOperation(_currentAccount.AccountNumber, "withdraw", amount, DateTime.Today.ToString("yyyy-MM-dd", new NumberFormatInfo()), DateTime.Now.ToString("HH:mm:ss", new NumberFormatInfo()));
    }

    public int ViewBalance()
    {
        if (_currentAccount is null) throw new ArgumentException("current account is null");
        return _currentAccount.Balance;
    }

    public Collection<Operation> ViewHistory()
    {
        if (_currentAccount is null) throw new ArgumentException("current account is null");
        return _currentAccount.Operations;
    }
}