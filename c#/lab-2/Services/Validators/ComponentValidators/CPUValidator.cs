using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class CPUValidator : IComponentValidator<CPU>
{
    public ResultBase Validate(CPU item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.CoresFrequency <= 0)
        {
            return new InvalidComponent<CPU>("Invalid CPU Cores Frequency");
        }

        if (item.CoresCount <= 0)
        {
            return new InvalidComponent<CPU>("Invalid CPU Cores Count");
        }

        if (item.MemoryFrequency <= 0)
        {
            return new InvalidComponent<CPU>("Invalid CPU Memory Frequency");
        }

        if (item.HeatDissipation <= 0)
        {
            return new InvalidComponent<CPU>("Invalid CPU Heat Dissipation");
        }

        if (item.PowerConsumption <= 0)
        {
            return new InvalidComponent<CPU>("Invalid CPU Power Consumption");
        }

        return new ValidComponent<CPU>(item);
    }
}