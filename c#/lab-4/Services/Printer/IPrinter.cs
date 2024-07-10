using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.Printer;

public interface IPrinter
{
    public void PrintFile(IFile file);
    public void PrintCatalog(IFileSystemComponent root, int depth);
}