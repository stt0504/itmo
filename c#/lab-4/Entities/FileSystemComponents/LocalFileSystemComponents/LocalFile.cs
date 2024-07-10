using System.IO;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.LocalFileSystemComponents;

public class LocalFile : LocalFileSystemComponent, IFile
{
    public LocalFile(string name, string path)
        : base(name, path)
    {
        Data = File.ReadAllText(path);
    }

    public string Data { get; set; }
    public override LocalFile Clone()
    {
        return new LocalFile(Name, Path)
        {
            Data = this.Data,
        };
    }

    public override void Delete()
    {
        File.Delete(Path);
    }
}