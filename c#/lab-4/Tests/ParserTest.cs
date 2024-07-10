using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.Commands;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.MemoryFileSystemComponents;
using Itmo.ObjectOrientedProgramming.Lab4.Services.CommandFactories;
using Itmo.ObjectOrientedProgramming.Lab4.Services.FileSystemStrategy;
using Itmo.ObjectOrientedProgramming.Lab4.Services.FilesystemStrategyRepository;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Parser;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Printer;
using Itmo.ObjectOrientedProgramming.Lab4.Services.PrinterRepository;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Traversal;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab4.Tests;

public class ParserTest
{
    private readonly ICommandParser _parser;

    public ParserTest()
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
        _parser = new ConsoleCommandParser(commands, ' ', commandFactoryFacade);

        var strategyRepository = new StrategyRepository();
        var inMemoryStrategy = new InMemoryFileSystemStrategy();
        strategyRepository.Strategies.Add("in-memory", inMemoryStrategy);
        strategyRepository.Strategies.Add("local", new LocalFileSystemStrategy());

        var rootCatalog = new InMemoryCatalog("C:", null);
        rootCatalog.Components.Add(new InMemoryFile("file1", rootCatalog, "1"));
        var catalog1 = new InMemoryCatalog("catalog1", rootCatalog);
        catalog1.Components.Add(new InMemoryFile("file3", catalog1, "1"));
        catalog1.Components.Add(new InMemoryFile("file4", catalog1, "1"));
        catalog1.Components.Add(new InMemoryFile("file5", catalog1, "1"));
        catalog1.Components.Add(new InMemoryFile("file6", catalog1, "1"));
        rootCatalog.Components.Add(catalog1);
        rootCatalog.Components.Add(new InMemoryFile("file2", rootCatalog, "1"));

        inMemoryStrategy.Root = rootCatalog;

        var printerRepository = new PrinterRepository();
        printerRepository.Printers.Add("console", new ConsolePrinter(new CatalogTraversal()));
    }

    [Theory]
    [InlineData("connect C: -m in-memory", typeof(ConnectCommand), new[] { "-m", "in-memory" })]
    [InlineData("disconnect", typeof(DisconnectCommand), new string[] { })]
    [InlineData("tree goto catalog1", typeof(TreeGoToCommand), new string[] { })]
    [InlineData("tree list -d 2 -m console", typeof(TreeListCommand), new[] { "-d", "2", "-m", "console" })]
    [InlineData("file show C:\\file2 -m console", typeof(FileShowCommand), new[] { "-m", "console" })]
    [InlineData("file move file3 file7", typeof(FileMoveCommand), new string[] { })]
    [InlineData("file copy file4 file8", typeof(FileCopyCommand), new string[] { })]
    [InlineData("file delete C:\\catalog1\\file5", typeof(FileDeleteCommand), new string[] { })]
    [InlineData("file rename C:\\catalog1\\file5 file10", typeof(FileRenameCommand), new string[] { })]
    public void TestParser(string input, Type commandTypeExpected, string[] expectedFlagParameters)
    {
        ICommand command = _parser.ParseCommand(input);
        Assert.Equal(commandTypeExpected, command.GetType());
        if (expectedFlagParameters == null) throw new ArgumentNullException(nameof(expectedFlagParameters));

        for (int i = 0; i < expectedFlagParameters.Length; i += 2)
        {
            Assert.Equal(expectedFlagParameters[i], command.Flags[i / 2].ShortName);
            Assert.Equal(expectedFlagParameters[i + 1], command.Flags[i / 2].Value);
        }
    }
}