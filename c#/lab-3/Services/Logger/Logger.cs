using System;
using Itmo.ObjectOrientedProgramming.Lab3.Models;

namespace Itmo.ObjectOrientedProgramming.Lab3.Services.Logger;

public class Logger : ILogger
{
    public Logger(IPrinter printer)
    {
        Printer = printer;
    }

    public IPrinter Printer { get; private set; }

    public void Log(Message message)
    {
        if (message == null) throw new ArgumentNullException(nameof(message));
        Printer.Write(message.Heading);
        Printer.Write(message.Body);
    }
}