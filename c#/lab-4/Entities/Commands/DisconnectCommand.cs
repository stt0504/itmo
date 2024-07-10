using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

public class DisconnectCommand : CommandBase
{
    public DisconnectCommand(Collection<Flag> flags)
        : base(flags)
    {
    }

    public override void Execute(FileSystem fileSystem)
    {
        if (fileSystem is null) throw new ArgumentNullException(nameof(fileSystem));

        fileSystem.Strategy = null;
        fileSystem.CurrentDirectory = null;
    }
}