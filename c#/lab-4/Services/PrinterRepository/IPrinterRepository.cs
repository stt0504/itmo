using Itmo.ObjectOrientedProgramming.Lab4.Services.Printer;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.PrinterRepository;

public interface IPrinterRepository
{
    public IPrinter GetPrinter(string name);
}