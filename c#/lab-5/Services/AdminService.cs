using System.Collections.ObjectModel;
using Lab05.Entities;
using Lab05.Entities.DatabaseManager;
using Lab05.Models;

namespace Lab05.Services;

public class AdminService : IAdminService
{
    private readonly string _password;
    private readonly IDataManager _manager;

    public AdminService(string password, IDataManager manager)
    {
        _password = password;
        _manager = manager;
    }

    public void Login(string password)
    {
        if (password != _password)
        {
            throw new ArgumentException("Incorrect system password");
        }
    }

    public int ViewBalance(int accountNumber)
    {
        Account? account = _manager.GetAccount(accountNumber).Result;
        if (account is null) throw new ArgumentException("account is null");
        return account.Balance;
    }

    public Collection<Operation> ViewHistory(int accountNumber)
    {
        Account? account = _manager.GetAccount(accountNumber).Result;
        if (account is null) throw new ArgumentException("account is null");
        return account.Operations;
    }
}