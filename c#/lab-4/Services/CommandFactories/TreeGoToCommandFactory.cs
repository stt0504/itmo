using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.CommandFactories;

public class TreeGoToCommandFactory : ICommandFactory
{
    public ICommand CreateCommand(Collection<Flag> flags, string[] parameters)
    {
        if (parameters == null) throw new ArgumentNullException(nameof(parameters));
        return new TreeGoToCommand(flags, parameters[0]);
    }
}