namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.LocalFileSystemComponents;

public abstract class LocalFileSystemComponent : IFileSystemComponent
{
    protected LocalFileSystemComponent(string name, string path)
    {
        Name = name;
        Path = path;
    }

    public string Name { get; }
    public string Path { get; private set; }

    public abstract IFileSystemComponent Clone();

    public abstract void Delete();
}