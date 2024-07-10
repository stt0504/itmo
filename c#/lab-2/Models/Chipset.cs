namespace Itmo.ObjectOrientedProgramming.Lab2.Models;

public class Chipset
{
    public Chipset(string name)
    {
        Name = name;
    }

    public string Name { get; private set; }
}