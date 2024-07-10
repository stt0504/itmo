using System.Collections.ObjectModel;
using Lab05.Models;

namespace Lab05.Services;

public interface IAdminService
{
    public void Login(string password);
    public int ViewBalance(int accountNumber);
    public Collection<Operation> ViewHistory(int accountNumber);
}