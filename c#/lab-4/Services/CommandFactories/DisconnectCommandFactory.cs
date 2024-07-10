using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.CommandFactories;

public class DisconnectCommandFactory : ICommandFactory
{
    public ICommand CreateCommand(Collection<Flag> flags, string[] parameters)
    {
        return new DisconnectCommand(flags);
    }
}