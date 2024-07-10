using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.Traversal;

public interface ICatalogTraversal
{
    IFileSystemComponent Traverse(IFileSystemComponent root);
}