using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.FileSystemStrategy;

public interface IFileSystemStrategy
{
    public void CopyFile(string sourcePath, string destinationPath);
    public void DeleteFile(string path);

    public IFileSystemComponent GetComponent(string path);
}