using System;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.MemoryFileSystemComponents;

public abstract class InMemoryFileSystemComponent : IFileSystemComponent
{
    protected InMemoryFileSystemComponent(string name, InMemoryCatalog? parentCatalog)
    {
        Name = name;
        ParentCatalog = parentCatalog;
    }

    public string Name { get; }
    public InMemoryCatalog? ParentCatalog { get; }

    public void Delete()
    {
        if (ParentCatalog is null) throw new ArgumentException("Cannot delete the main catalog");
        ParentCatalog.Components.Remove(this);
    }

    public abstract IFileSystemComponent Clone();
}