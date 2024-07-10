using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class MotherboardValidator : IComponentValidator<Motherboard>
{
    public ResultBase Validate(Motherboard item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.SATAPortsCount <= 0)
        {
            return new InvalidComponent<Motherboard>("Invalid Motherboard SATA Ports Count");
        }

        if (item.PCIELinesCount <= 0)
        {
            return new InvalidComponent<Motherboard>("Invalid Motherboard PCI-e Lines Count");
        }

        if (item.SupportedDDRStandards.Count == 0)
        {
            return new InvalidComponent<Motherboard>("Invalid Motherboard Supported Standards");
        }

        if (item.RamSlotsNumber <= 0)
        {
            return new InvalidComponent<Motherboard>("Invalid Motherboard Ram Slots Number");
        }

        return new ValidComponent<Motherboard>(item);
    }
}