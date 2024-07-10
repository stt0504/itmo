using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class PowerUnitValidator : IComponentValidator<PowerSupplyUnit>
{
    public ResultBase Validate(PowerSupplyUnit item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.PeakLoad <= 0)
        {
            return new InvalidComponent<PowerSupplyUnit>("Invalid Power Supply Unit Peak Load");
        }

        return new ValidComponent<PowerSupplyUnit>(item);
    }
}