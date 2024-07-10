using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

public abstract class CommandBase : ICommand
{
    protected CommandBase(Collection<Flag> flags)
    {
        Flags = flags;
    }

    public Collection<Flag> Flags { get; }

    public abstract void Execute(FileSystem fileSystem);
}