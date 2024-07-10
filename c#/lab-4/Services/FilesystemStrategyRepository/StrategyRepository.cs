using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab4.Services.FileSystemStrategy;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.FilesystemStrategyRepository;

public class StrategyRepository : IStrategyRepository
{
    public Dictionary<string, IFileSystemStrategy> Strategies { get; } = new();

    public IFileSystemStrategy GetStrategy(string name)
    {
        return Strategies[name];
    }
}