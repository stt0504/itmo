using System;
using System.Collections.ObjectModel;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;
using Itmo.ObjectOrientedProgramming.Lab4.Models;
using Itmo.ObjectOrientedProgramming.Lab4.Services.CommandFactories;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.Parser;

public class ConsoleCommandParser : ICommandParser
{
    public ConsoleCommandParser(Collection<string> commands, char separator, CommandFactoryFacade commandFactoryFacade)
    {
        Commands = commands;
        Separator = separator;
        CommandFactoryFacade = commandFactoryFacade;
    }

    public Collection<string> Commands { get; }
    public char Separator { get; }
    public CommandFactoryFacade CommandFactoryFacade { get; }

    public ICommand ParseCommand(string input)
    {
        if (input == null) throw new ArgumentNullException(nameof(input));
        string command;
        string[] args;
        string[] flagArray;
        Collection<Flag> flags = new();

        foreach (string keyword in Commands)
        {
            if (!input.StartsWith(keyword, StringComparison.OrdinalIgnoreCase)) continue;
            command = keyword;
            int index = input.IndexOf('-', StringComparison.OrdinalIgnoreCase);
            if (index != -1)
            {
                args = input[keyword.Length..index]
                    .Split(Separator, StringSplitOptions.RemoveEmptyEntries).ToArray();
                flagArray = input[index..].Split(Separator, StringSplitOptions.RemoveEmptyEntries).ToArray();
                for (int i = 0; i < flagArray.Length; i += 2)
                {
                    string shortName = flagArray[i];
                    if (i + 1 < flagArray.Length)
                    {
                        string value = flagArray[i + 1];
                        flags.Add(new Flag(shortName, value));
                    }
                    else
                    {
                        throw new ArgumentException("last flag don't contain value");
                    }
                }
            }
            else
            {
                args = input[keyword.Length..].Split(Separator, StringSplitOptions.RemoveEmptyEntries).ToArray();
            }

            return CommandFactoryFacade.GetFactory(command).CreateCommand(flags, args);
        }

        throw new ArgumentException("Command is missing");
    }
}