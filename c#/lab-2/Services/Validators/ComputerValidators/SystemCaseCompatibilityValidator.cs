using System;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class SystemCaseCompatibilityValidator : IComputerValidator
{
    public ComputerValidationResultBase Validate(Computer item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        SystemCase systemCase = item.SystemCase;
        Motherboard motherboard = item.Motherboard;
        VideoCard? videoCard = item.VideoCard;
        CPUCoolingSystem cooler = item.Cooler;

        if (videoCard is not null && (videoCard.Width > systemCase.MaxVideoCardWidth ||
                                      videoCard.Length > systemCase.MaxVideoCardLength))
        {
            return new Failure("Error: the videocard does not fit into the case");
        }

        if (systemCase.SupportedFormFactors.All(formFactor => formFactor != motherboard.FormFactor))
        {
            return new Failure("Error: the case does not support this form factor of the motherboard");
        }

        if (cooler.Height > systemCase.Width)
        {
            return new Failure("Error: the cooler does not fit in the case");
        }

        return new Success(true, null, item);
    }
}