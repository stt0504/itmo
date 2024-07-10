using System;
using System.Collections.ObjectModel;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;
using Itmo.ObjectOrientedProgramming.Lab4.Models;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Printer;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

public class FileShowCommand : CommandBase
{
    public FileShowCommand(Collection<Flag> flags, string path)
        : base(flags)
    {
        Path = path;
    }

    public string Path { get; private set; }

    public override void Execute(FileSystem fileSystem)
    {
        if (fileSystem is null) throw new ArgumentNullException(nameof(fileSystem));
        if (fileSystem.CurrentDirectory is null) throw new ArgumentException("current directory is null");

        if (!Path.StartsWith(fileSystem.CurrentDirectory, StringComparison.CurrentCulture))
        {
            Path = System.IO.Path.Combine(fileSystem.CurrentDirectory, Path);
        }

        Flag mode = Flags.First(flag => flag.ShortName == "-m");
        IPrinter printer = fileSystem.PrinterRepository.GetPrinter(mode.Value);
        if (fileSystem.GetComponent(Path) is IFile file)
        {
            printer.PrintFile(file);
        }
    }
}