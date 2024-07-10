using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class SystemCaseValidator : IComponentValidator<SystemCase>
{
    public ResultBase Validate(SystemCase item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.Height <= 0)
        {
            return new InvalidComponent<SystemCase>("Invalid System Case Height");
        }

        if (item.Width <= 0)
        {
            return new InvalidComponent<SystemCase>("Invalid System Case Width");
        }

        if (item.SupportedFormFactors.Count == 0)
        {
            return new InvalidComponent<SystemCase>("Invalid System Case Supported Form Factors");
        }

        if (item.MaxVideoCardLength <= 0)
        {
            return new InvalidComponent<SystemCase>("Invalid System Case Max Video Card Length");
        }

        if (item.MaxVideoCardWidth <= 0)
        {
            return new InvalidComponent<SystemCase>("Invalid System Case Max Video Card Width");
        }

        return new ValidComponent<SystemCase>(item);
    }
}