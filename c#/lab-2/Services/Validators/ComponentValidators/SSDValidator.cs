using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class SSDValidator : IComponentValidator<SSD>
{
    public ResultBase Validate(SSD item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.Capacity <= 0)
        {
            return new InvalidComponent<SSD>("Invalid SSD Capacity");
        }

        if (item.MaxSpeed <= 0)
        {
            return new InvalidComponent<SSD>("Invalid SSD Max Speed");
        }

        if (item.PowerConsumption <= 0)
        {
            return new InvalidComponent<SSD>("Invalid SSD Power Consumption");
        }

        return new ValidComponent<SSD>(item);
    }
}