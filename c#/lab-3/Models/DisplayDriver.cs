using System;
using Itmo.ObjectOrientedProgramming.Lab3.Services;
using static Crayon.Output;

namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public class DisplayDriver : IDisplayDriver
{
    private IPrinter _printer;

    public DisplayDriver(IPrinter printer)
    {
        _printer = printer;
    }

    public Color Color { get; private set; } = new(255, 255, 255);

    public void Clear()
    {
        _printer.Clear();
    }

    public void SetColor(Color color)
    {
        Color = color;
    }

    public void PrintMessage(Message message)
    {
        if (message == null) throw new ArgumentNullException(nameof(message));

        string heading = Rgb(Color.R, Color.B, Color.G).Text(message.Heading);
        string body = Rgb(Color.R, Color.B, Color.G).Text(message.Body);

        _printer.Write(heading);
        _printer.Write(body);
    }
}