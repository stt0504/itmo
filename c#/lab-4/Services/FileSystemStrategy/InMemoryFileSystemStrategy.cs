using System;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.MemoryFileSystemComponents;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.FileSystemStrategy;

public class InMemoryFileSystemStrategy : IFileSystemStrategy
{
    public InMemoryCatalog? Root { get; set; }

    public void CopyFile(string sourcePath, string destinationPath)
    {
        var source = new Path(sourcePath);
        var dest = new Path(destinationPath);
        if (Root is null) throw new ArgumentException("Root is null");
        IFileSystemComponent componentToCopy = source.GetFileSystemComponent(Root);
        dest.SetFileSystemComponent(Root, componentToCopy);
    }

    public void DeleteFile(string path)
    {
        var source = new Path(path);
        if (Root is null) throw new ArgumentException("Root is null");
        source.DeleteFile(Root);
    }

    public IFileSystemComponent GetComponent(string path)
    {
        var source = new Path(path);
        if (Root is null) throw new ArgumentException("Root is null");
        return source.GetFileSystemComponent(Root);
    }
}