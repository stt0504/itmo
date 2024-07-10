using Itmo.ObjectOrientedProgramming.Lab3.Models;

namespace Itmo.ObjectOrientedProgramming.Lab3.Services.Logger;

public interface ILogger
{
    public void Log(Message message);
}