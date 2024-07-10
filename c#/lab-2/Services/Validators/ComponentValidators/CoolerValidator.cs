using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class CoolerValidator : IComponentValidator<CPUCoolingSystem>
{
    public ResultBase Validate(CPUCoolingSystem item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.Height <= 0)
        {
            return new InvalidComponent<CPUCoolingSystem>("Invalid Cooler Height");
        }

        if (item.Width <= 0)
        {
            return new InvalidComponent<CPUCoolingSystem>("Invalid Cooler Width");
        }

        if (item.Length <= 0)
        {
            return new InvalidComponent<CPUCoolingSystem>("Invalid Cooler Length");
        }

        if (item.SupportedSockets.Count < 1)
        {
            return new InvalidComponent<CPUCoolingSystem>("Invalid Cooler Supported Sockets");
        }

        if (item.MaxHeatDissipation <= 0)
        {
            return new InvalidComponent<CPUCoolingSystem>("Invalid Cooler Max Heat Dissipation");
        }

        return new ValidComponent<CPUCoolingSystem>(item);
    }
}