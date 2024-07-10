namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public interface IMessenger : IAddressee
{
    public void PrintMessage(Message message);
}