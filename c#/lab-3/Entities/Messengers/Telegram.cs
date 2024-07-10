using System;
using Itmo.ObjectOrientedProgramming.Lab3.Services;

namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public class Telegram : MessengerBase
{
    public Telegram(IPrinter printer)
        : base(printer)
    {
    }

    public override void PrintMessage(Message message)
    {
        if (message == null) throw new ArgumentNullException(nameof(message));
        Printer.Write("[Telegram]:");
        Printer.Write(message.Heading);
        Printer.Write(message.Body);
    }
}