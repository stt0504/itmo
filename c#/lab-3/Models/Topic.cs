namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public class Topic
{
    public Topic(string name, IAddressee addressee)
    {
        Name = name;
        Addressee = addressee;
    }

    public string Name { get; private set; }
    public IAddressee Addressee { get; private set; }

    public void SendMessage(Message message)
    {
        Addressee.ReceiveMessage(message);
    }
}