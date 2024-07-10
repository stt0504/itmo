using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab3.Services.Logger;

namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public class Display : IDisplay
{
    private ILogger? _logger;
    private DisplayDriver _driver;
    private Collection<Message> _messages = new();
    private ImportanceLevel? _filter = ImportanceLevel.Level1;

    public Display(DisplayDriver driver)
    {
        _driver = driver;
    }

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
        _filter = importanceLevel;
    }

    public void DisableFilter()
    {
        _filter = ImportanceLevel.Level1;
    }

    public void SetColor(Color color)
    {
        _driver.SetColor(color);
    }

    public void PrintMessage()
    {
        _driver.Clear();
        _driver.PrintMessage(_messages[^1]);
    }

    public void ReceiveMessage(Message message)
    {
        if (message == null) throw new ArgumentNullException(nameof(message));
        if (message.ImportanceLevel < _filter) return;
        _messages.Add(message);
        _logger?.Log(message);
    }
}