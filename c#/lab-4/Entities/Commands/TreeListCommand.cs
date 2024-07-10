using System;
using System.Collections.ObjectModel;
using System.Globalization;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab4.Models;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Printer;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;

public class TreeListCommand : CommandBase
{
    public TreeListCommand(Collection<Flag> flags)
        : base(flags)
    {
    }

    public int Depth { get; private set; }

    public override void Execute(FileSystem fileSystem)
    {
        if (fileSystem is null) throw new ArgumentNullException(nameof(fileSystem));
        if (fileSystem.CurrentDirectory is null) throw new ArgumentException("current directory is null");

        Flag? depthFlag = Flags.FirstOrDefault(flag => flag.ShortName == "-d");
        Depth = 1;
        if (depthFlag is not null)
        {
            Depth = int.Parse(depthFlag.Value, CultureInfo.CurrentCulture);
        }

        Flag mode = Flags.First(flag => flag.ShortName == "-m");
        IPrinter printer = fileSystem.PrinterRepository.GetPrinter(mode.Value);
        printer.PrintCatalog(fileSystem.GetComponent(fileSystem.CurrentDirectory), Depth);
    }
}