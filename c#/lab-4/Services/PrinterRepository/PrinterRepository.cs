using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Printer;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.PrinterRepository;

public class PrinterRepository : IPrinterRepository
{
    public Dictionary<string, IPrinter> Printers { get; } = new();

    public IPrinter GetPrinter(string name)
    {
        return Printers[name];
    }
}