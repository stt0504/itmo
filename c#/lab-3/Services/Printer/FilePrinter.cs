using System.IO;

namespace Itmo.ObjectOrientedProgramming.Lab3.Services;

public class FilePrinter : IPrinter
{
    private string filePath;

    public FilePrinter(string filePath)
    {
        this.filePath = filePath;
    }

    public void Write(string text)
    {
        File.AppendAllText(filePath, text);
    }

    public void Clear()
    {
        File.WriteAllText(filePath, string.Empty);
    }
}