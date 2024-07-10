using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class HDDValidator : IComponentValidator<HDD>
{
    public ResultBase Validate(HDD item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.Capacity <= 0)
        {
            return new InvalidComponent<HDD>("Invalid HDD Capacity");
        }

        return new ValidComponent<HDD>(item);
    }
}