using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab3.Services.Logger;

namespace Itmo.ObjectOrientedProgramming.Lab3.Models;

public class Group : IAddressee
{
    public Group(Collection<IAddressee> addressees)
    {
        Addressees = addressees;
    }

    public Collection<IAddressee> Addressees { get; private set; }

    public void ReceiveMessage(Message message)
    {
        foreach (IAddressee addressee in Addressees)
        {
            addressee.ReceiveMessage(message);
        }
    }

    public void EnableLogging(ILogger logger)
    {
        foreach (IAddressee addressee in Addressees)
        {
            addressee.EnableLogging(logger);
        }
    }

    public void DisableLogging()
    {
        foreach (IAddressee addressee in Addressees)
        {
            addressee.DisableLogging();
        }
    }

    public void EnableFilter(ImportanceLevel importanceLevel)
    {
        foreach (IAddressee addressee in Addressees)
        {
            addressee.EnableFilter(importanceLevel);
        }
    }

    public void DisableFilter()
    {
        foreach (IAddressee addressee in Addressees)
        {
            addressee.DisableFilter();
        }
    }
}