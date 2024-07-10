using System.Collections.ObjectModel;
using Lab05.Models;

namespace Lab05.Services;

public interface IUserService
{
    public void CreateAccount(int accountNumber, int pin);
    public void Login(int accountNumber, int pin);
    public void Deposit(int amount);
    public void Withdraw(int amount);
    public int ViewBalance();
    public Collection<Operation> ViewHistory();
}