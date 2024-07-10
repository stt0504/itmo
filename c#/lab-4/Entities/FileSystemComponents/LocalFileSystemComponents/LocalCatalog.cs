using System.Collections.ObjectModel;
using System.IO;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.LocalFileSystemComponents;

public class LocalCatalog : LocalFileSystemComponent, ICatalog
{
    public LocalCatalog(string name, string path)
        : base(name, path)
    {
    }

    public Collection<IFileSystemComponent> Components { get; } = new();
    public override LocalCatalog Clone()
    {
        var clonedCatalog = new LocalCatalog(Name, Path);

        foreach (IFileSystemComponent component in Components)
        {
            clonedCatalog.Components.Add(component.Clone());
        }

        return clonedCatalog;
    }

    public override void Delete()
    {
        Directory.Delete(Path);
    }
}