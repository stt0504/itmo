using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Models;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

public class FileMoveCommand : CommandBase
{
    public FileMoveCommand(Collection<Flag> flags, string sourcePath, string destinationPath)
        : base(flags)
    {
        SourcePath = sourcePath;
        DestinationPath = destinationPath;
    }

    public string SourcePath { get; private set; }
    public string DestinationPath { get; private set; }

    public override void Execute(FileSystem fileSystem)
    {
        if (fileSystem is null) throw new ArgumentNullException(nameof(fileSystem));
        if (fileSystem.CurrentDirectory is null) throw new ArgumentException("current directory is null");

        if (!SourcePath.StartsWith(fileSystem.CurrentDirectory, StringComparison.CurrentCulture))
        {
            SourcePath = System.IO.Path.Combine(fileSystem.CurrentDirectory, SourcePath);
        }

        if (!DestinationPath.StartsWith(fileSystem.CurrentDirectory, StringComparison.CurrentCulture))
        {
            DestinationPath = System.IO.Path.Combine(fileSystem.CurrentDirectory, DestinationPath);
        }

        fileSystem.CopyFile(SourcePath, DestinationPath);
        fileSystem.DeleteFile(SourcePath);
    }
}