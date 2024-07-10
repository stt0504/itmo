using Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.Parser;

public interface ICommandParser
{
    ICommand ParseCommand(string input);
}