using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.MemoryFileSystemComponents;

public class InMemoryCatalog : InMemoryFileSystemComponent, ICatalog
{
    public InMemoryCatalog(string name, InMemoryCatalog? parentCatalog)
        : base(name, parentCatalog)
    {
    }

    public Collection<IFileSystemComponent> Components { get; } = new();

    public override InMemoryCatalog Clone()
    {
        var clonedCatalog = new InMemoryCatalog(Name, ParentCatalog);

        foreach (IFileSystemComponent component in Components)
        {
            clonedCatalog.Components.Add(component.Clone());
        }

        return clonedCatalog;
    }
}