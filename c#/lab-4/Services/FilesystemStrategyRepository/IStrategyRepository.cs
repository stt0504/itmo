using Itmo.ObjectOrientedProgramming.Lab4.Services.FileSystemStrategy;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.FilesystemStrategyRepository;

public interface IStrategyRepository
{
    IFileSystemStrategy GetStrategy(string name);
}