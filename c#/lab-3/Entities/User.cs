using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab3.Services.Logger;

namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public class User : IUser
{
    private ImportanceLevel _filter = ImportanceLevel.Level1;
    private ILogger? _logger;
    private Collection<MessageStatus> _messageStatuses = new();

    public User(string name)
    {
        Name = name;
    }

    public Collection<Message> Messages { get; private set; } = new();

    public string Name { get; }

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

    public void MarkMessageAsRead(Message message)
    {
        int index = Messages.IndexOf(message);
        if (index < 0 || index >= _messageStatuses.Count) throw new ArgumentException("No such message");
        if (_messageStatuses[index] is MessageStatus.Read)
        {
            throw new ArgumentException("Message is already read");
        }

        _messageStatuses[index] = MessageStatus.Read;
    }

    public MessageStatus GetMessageStatus(Message message)
    {
        int index = Messages.IndexOf(message);
        if (index < 0 || index >= _messageStatuses.Count) throw new ArgumentException("No such message");
        return _messageStatuses[index];
    }

    public void ReceiveMessage(Message message)
    {
        if (message == null) throw new ArgumentNullException(nameof(message));
        if (message.ImportanceLevel < _filter) return;
        Messages.Add(message);
        _messageStatuses.Add(MessageStatus.Unread);
        _logger?.Log(message);
    }
}