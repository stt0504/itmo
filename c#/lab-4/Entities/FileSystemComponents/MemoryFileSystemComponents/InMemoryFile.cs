namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.MemoryFileSystemComponents;

public class InMemoryFile : InMemoryFileSystemComponent, IFile
{
    public InMemoryFile(string name, InMemoryCatalog? parentCatalog, string data)
        : base(name, parentCatalog)
    {
        Data = data;
    }

    public string Data { get; }

    public override InMemoryFile Clone()
    {
        return new InMemoryFile(Name, ParentCatalog, Data);
    }
}