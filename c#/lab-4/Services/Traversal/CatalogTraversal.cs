using System;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.Traversal;

public class CatalogTraversal : ICatalogTraversal
{
    public IFileSystemComponent Traverse(IFileSystemComponent root)
    {
        if (root is null) throw new ArgumentNullException(nameof(root));
        IFileSystemComponent rootCopy = root.Clone();
        return rootCopy;
    }
}