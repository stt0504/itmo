using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class RAMValidator : IComponentValidator<RAM>
{
    public ResultBase Validate(RAM item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.MemorySize <= 0)
        {
            return new InvalidComponent<RAM>("Invalid RAM Memory Size");
        }

        if (item.PowerConsumption <= 0)
        {
            return new InvalidComponent<RAM>("Invalid RAM PowerConsumption");
        }

        return new ValidComponent<RAM>(item);
    }
}