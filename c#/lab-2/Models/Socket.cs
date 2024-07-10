namespace Itmo.ObjectOrientedProgramming.Lab2.Models;

public class Socket
{
    public Socket(string name)
    {
        Name = name;
    }

    public string Name { get; private set; }
}