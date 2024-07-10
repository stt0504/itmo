using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class WifiAdapterValidator : IComponentValidator<WiFiAdapter>
{
    public ResultBase Validate(WiFiAdapter item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.PowerConsumption <= 0)
        {
            return new InvalidComponent<WiFiAdapter>("Invalid WiFi Power Consumption");
        }

        return new ValidComponent<WiFiAdapter>(item);
    }
}