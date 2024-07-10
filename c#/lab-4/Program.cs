using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Entities;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;
using Itmo.ObjectOrientedProgramming.Lab4.Services.CommandFactories;
using Itmo.ObjectOrientedProgramming.Lab4.Services.FileSystemStrategy;
using Itmo.ObjectOrientedProgramming.Lab4.Services.FilesystemStrategyRepository;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Parser;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Printer;
using Itmo.ObjectOrientedProgramming.Lab4.Services.PrinterRepository;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Traversal;

namespace Itmo.ObjectOrientedProgramming.Lab4;

public static class Program
{
    public static void Main()
    {
        var commandFactoryFacade = new CommandFactoryFacade();
        commandFactoryFacade.AddCommandFactory("connect", new ConnectCommandFactory());
        commandFactoryFacade.AddCommandFactory("disconnect", new DisconnectCommandFactory());
        commandFactoryFacade.AddCommandFactory("tree goto", new TreeGoToCommandFactory());
        commandFactoryFacade.AddCommandFactory("tree list", new TreeListCommandFactory());
        commandFactoryFacade.AddCommandFactory("file show", new FileShowCommandFactory());
        commandFactoryFacade.AddCommandFactory("file move", new FileMoveCommandFactory());
        commandFactoryFacade.AddCommandFactory("file copy", new FileCopyCommandFactory());
        commandFactoryFacade.AddCommandFactory("file delete", new FileDeleteCommandFactory());
        commandFactoryFacade.AddCommandFactory("file rename", new FileRenameCommandFactory());
        var commands = new Collection<string>
        {
            "connect", "disconnect", "tree goto", "tree list", "file show", "file move", "file copy", "file delete",
            "file rename",
        };
        var parser = new ConsoleCommandParser(commands, ' ', commandFactoryFacade);

        var strategyRepository = new StrategyRepository();
        strategyRepository.Strategies.Add("local", new LocalFileSystemStrategy());

        var printerRepository = new PrinterRepository();
        printerRepository.Printers.Add("console", new ConsolePrinter(new CatalogTraversal()));

        var fileSystem = new FileSystem(strategyRepository, printerRepository);

        string? input;
        do
        {
            input = Console.ReadLine();
            if (string.IsNullOrEmpty(input)) continue;
            ICommand command = parser.ParseCommand(input);
            command.Execute(fileSystem);
        }
        while (!string.IsNullOrEmpty(input));
    }
}