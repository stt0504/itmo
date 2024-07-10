namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;

public interface IFileSystemComponent
{
    public string Name { get; }
    IFileSystemComponent Clone();
    void Delete();
}