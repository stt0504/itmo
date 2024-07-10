using System;
using Itmo.ObjectOrientedProgramming.Lab3.Models;
using Itmo.ObjectOrientedProgramming.Lab3.Services;
using Itmo.ObjectOrientedProgramming.Lab3.Services.Logger;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests;

public class Tests
{
    private Message.Builder _messageBuilder = new();

    [Fact]
    public void SaveUnreadMessageTest()
    {
        Message defaultMessage = GetDefaultMessageBuilder().Build();
        var user = new User("user");
        user.ReceiveMessage(defaultMessage);
        Assert.Equal(MessageStatus.Unread, user.GetMessageStatus(defaultMessage));
    }

    [Fact]
    public void MarkAsReadToUnreadMessageTest()
    {
        Message defaultMessage = GetDefaultMessageBuilder().Build();
        var user = new User("user");
        user.ReceiveMessage(defaultMessage);
        user.MarkMessageAsRead(defaultMessage);
        Assert.Equal(MessageStatus.Read, user.GetMessageStatus(defaultMessage));
    }

    [Fact]
    public void MarkAsReadToReadMessageTest()
    {
        Message defaultMessage = GetDefaultMessageBuilder().Build();
        var user = new User("user");
        user.ReceiveMessage(defaultMessage);
        user.MarkMessageAsRead(defaultMessage);
        Assert.Throws<ArgumentException>(() =>
        {
            user.MarkMessageAsRead(defaultMessage);
        });
    }

    [Theory]
    [InlineData(ImportanceLevel.Level1, ImportanceLevel.Level2)]
    [InlineData(ImportanceLevel.Level2, ImportanceLevel.Level3)]
    public void UnimportantMessageTest(ImportanceLevel messageLevel, ImportanceLevel addresseeFilter)
    {
        Message unimportantMessage = GetDefaultMessageBuilder().SetImportanceLevel(messageLevel).Build();
        var user = new User("user");
        user.EnableFilter(addresseeFilter);
        user.ReceiveMessage(unimportantMessage);
        Assert.Empty(user.Messages);
    }

    [Fact]
    public void EnableLoggingTest()
    {
        Message defaultMessage = GetDefaultMessageBuilder().Build();
        var user = new User("user");
        var logger = new MockLogger();
        user.EnableLogging(logger);
        user.ReceiveMessage(defaultMessage);
        Assert.Equal(1, logger.CallsNumber);
    }

    [Fact]
    public void MessengerPrintTest()
    {
        Message defaultMessage = GetDefaultMessageBuilder().Build();
        var printer = new MockPrinter();
        var messenger = new Telegram(printer);
        messenger.ReceiveMessage(defaultMessage);
        messenger.PrintMessage(defaultMessage);
        Assert.Equal("[Telegram]:\nheading\nbody\n", printer.Output);
    }

    private Message.Builder GetDefaultMessageBuilder()
    {
        return _messageBuilder.SetHeading("heading")
            .SetBody("body");
    }

    private class MockPrinter : IPrinter
    {
        public string Output { get; private set; } = string.Empty;

        public void Write(string text)
        {
            Output += text + '\n';
        }

        public void Clear()
        {
            Output = string.Empty;
        }
    }

    private class MockLogger : ILogger
    {
        public int CallsNumber { get; private set; }

        public void Log(Message message)
        {
            CallsNumber++;
        }
    }
}