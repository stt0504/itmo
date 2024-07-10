using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

public interface ICommand
{
    public Collection<Flag> Flags { get; }
    void Execute(FileSystem fileSystem);
}