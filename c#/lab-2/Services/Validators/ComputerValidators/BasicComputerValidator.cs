using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class BasicComputerValidator : IComputerValidator
{
    public ComputerValidationResultBase Validate(Computer item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (!item.CPU.HasVideoCore && item.VideoCard is null)
        {
            return new Failure("Error: Image output is not possible");
        }

        if (item.SSD is null && item.HDD is null)
        {
            return new Failure("Error: At least one storage device is required");
        }

        return new Success(true, null, item);
    }
}