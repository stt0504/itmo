using System;

namespace Itmo.ObjectOrientedProgramming.Lab3.Services;

public class ConsolePrinter : IPrinter
{
    public void Write(string text)
    {
        Console.WriteLine(text);
    }

    public void Clear()
    {
        Console.Clear();
    }
}