using System;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;
using Itmo.ObjectOrientedProgramming.Lab4.Services.FileSystemStrategy;
using Itmo.ObjectOrientedProgramming.Lab4.Services.FilesystemStrategyRepository;
using Itmo.ObjectOrientedProgramming.Lab4.Services.PrinterRepository;

namespace Itmo.ObjectOrientedProgramming.Lab4.Entities;

public class FileSystem
{
    public FileSystem(IStrategyRepository strategyRepository, IPrinterRepository printerRepository)
    {
        StrategyRepository = strategyRepository;
        PrinterRepository = printerRepository;
    }

    public IStrategyRepository StrategyRepository { get; }
    public IPrinterRepository PrinterRepository { get; }
    public IFileSystemStrategy? Strategy { get; set; }
    public string? CurrentDirectory { get; set; }

    public void CopyFile(string sourcePath, string destinationPath)
    {
        if (Strategy is null) throw new ArgumentException("Strategy is null");
        Strategy.CopyFile(sourcePath, destinationPath);
    }

    public void DeleteFile(string path)
    {
        if (Strategy is null) throw new ArgumentException("Strategy is null");
        Strategy.DeleteFile(path);
    }

    public IFileSystemComponent GetComponent(string path)
    {
        if (Strategy is null) throw new ArgumentException("Strategy is null");
        return Strategy.GetComponent(path);
    }
}