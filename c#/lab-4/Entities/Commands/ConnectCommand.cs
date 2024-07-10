using System;
using System.Collections.ObjectModel;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

public class ConnectCommand : CommandBase
{
    public ConnectCommand(Collection<Flag> flags, string path)
        : base(flags)
    {
        Path = path;
    }

    public string Path { get; }

    public override void Execute(FileSystem fileSystem)
    {
        if (fileSystem is null) throw new ArgumentNullException(nameof(fileSystem));

        Flag mode = Flags.First(flag => flag.ShortName == "-m");
        fileSystem.Strategy = fileSystem.StrategyRepository.GetStrategy(mode.Value);
        fileSystem.CurrentDirectory = Path;
    }
}