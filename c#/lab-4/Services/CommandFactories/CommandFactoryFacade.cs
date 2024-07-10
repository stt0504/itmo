using System.Collections.Generic;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.CommandFactories;

public class CommandFactoryFacade
{
    public Dictionary<string, ICommandFactory> Factories { get; } = new();

    public void AddCommandFactory(string name, ICommandFactory factory)
    {
        Factories.Add(name, factory);
    }

    public ICommandFactory GetFactory(string commandName)
    {
        return Factories[commandName];
    }
}