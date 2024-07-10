namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public interface IUser : IAddressee
{
    public void MarkMessageAsRead(Message message);
}