using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class BIOS
{
    public BIOS(string type, string version, Collection<CPU?> supportedProcessors)
    {
        Type = type;
        Version = version;
        SupportedProcessors = supportedProcessors;
    }

    public string Type { get; private set; }
    public string Version { get; private set; }
    public Collection<CPU?> SupportedProcessors { get; private set; }
}