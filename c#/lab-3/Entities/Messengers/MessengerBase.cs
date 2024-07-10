using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab3.Services;
using Itmo.ObjectOrientedProgramming.Lab3.Services.Logger;

namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public abstract class MessengerBase : IMessenger
{
    private ILogger? _logger;

    protected MessengerBase(IPrinter printer)
    {
        Printer = printer;
    }

    public Collection<Message> Messages { get; private set; } = new();
    protected IPrinter Printer { get; set; }
    protected ImportanceLevel Filter { get; set; } = ImportanceLevel.Level1;
    public abstract void PrintMessage(Message message);

    public void EnableLogging(ILogger logger)
    {
        _logger = logger;
    }

    public void DisableLogging()
    {
        _logger = null;
    }

    public void EnableFilter(ImportanceLevel importanceLevel)
    {
        Filter = importanceLevel;
    }

    public void DisableFilter()
    {
        Filter = ImportanceLevel.Level1;
    }

    public void ReceiveMessage(Message message)
    {
        if (message == null) throw new ArgumentNullException(nameof(message));
        if (message.ImportanceLevel < Filter) return;
        Messages.Add(message);
        _logger?.Log(message);
    }
}