using System;
using Itmo.ObjectOrientedProgramming.Lab3.Services;

namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public class Whatsapp : MessengerBase
{
    public Whatsapp(IPrinter printer)
        : base(printer)
    {
    }

    public override void PrintMessage(Message message)
    {
        if (message == null) throw new ArgumentNullException(nameof(message));
        Printer.Write("[Whatsapp]:");
        Printer.Write(message.Heading);
        Printer.Write(message.Body);
    }
}