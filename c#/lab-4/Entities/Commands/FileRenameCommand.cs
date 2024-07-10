using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

public class FileRenameCommand : CommandBase
{
    public FileRenameCommand(Collection<Flag> flags, string path, string newName)
        : base(flags)
    {
        Path = path;
        NewName = newName;
    }

    public string Path { get; private set; }
    public string NewName { get; }

    public override void Execute(FileSystem fileSystem)
    {
        if (fileSystem is null) throw new ArgumentNullException(nameof(fileSystem));
        if (fileSystem.CurrentDirectory is null) throw new ArgumentException("current directory is null");

        if (!Path.StartsWith(fileSystem.CurrentDirectory, StringComparison.CurrentCulture))
        {
            Path = System.IO.Path.Combine(fileSystem.CurrentDirectory, Path);
        }

        string directory = System.IO.Path.GetDirectoryName(Path) ?? throw new ArgumentException("directory is null");
        string newPath = System.IO.Path.Combine(directory, NewName);

        fileSystem.CopyFile(Path, newPath);
        fileSystem.DeleteFile(Path);
    }
}