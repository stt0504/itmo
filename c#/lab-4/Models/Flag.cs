namespace Itmo.ObjectOrientedProgramming.Lab4.Models;

public class Flag
{
    public Flag(string shortName, string value)
    {
        ShortName = shortName;
        Value = value;
    }

    public string Value { get; private set; }
    public string ShortName { get; private set; }
}