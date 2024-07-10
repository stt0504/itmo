using Itmo.ObjectOrientedProgramming.Lab3.Services.Logger;

namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public interface IAddressee
{
    public void ReceiveMessage(Message message);
    public void EnableLogging(ILogger logger);
    public void DisableLogging();
    public void EnableFilter(ImportanceLevel importanceLevel);
    public void DisableFilter();
}