using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;

public interface ICatalog : IFileSystemComponent
{
    public Collection<IFileSystemComponent> Components { get; }
}