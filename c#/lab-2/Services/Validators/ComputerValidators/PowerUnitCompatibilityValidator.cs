using System;
using System.Collections.ObjectModel;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class PowerUnitCompatibilityValidator : IComputerValidator
{
    public ComputerValidationResultBase Validate(Computer item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        PowerSupplyUnit powerUnit = item.PowerSupplyUnit;
        CPU cpu = item.CPU;
        Collection<RAM> rams = item.RAM;
        VideoCard? videoCard = item.VideoCard;
        SSD? ssd = item.SSD;
        HDD? hdd = item.HDD;
        WiFiAdapter? wiFiAdapter = item.WiFiAdapter;

        double sumPowerConsumption = cpu.PowerConsumption + rams.Sum(ramModule => ramModule.PowerConsumption);

        if (videoCard is not null)
        {
            sumPowerConsumption += videoCard.PowerConsumption;
        }

        if (ssd is not null)
        {
            sumPowerConsumption += ssd.PowerConsumption;
        }

        if (hdd is not null)
        {
            sumPowerConsumption += hdd.PowerConsumption;
        }

        if (wiFiAdapter is not null)
        {
            sumPowerConsumption += wiFiAdapter.PowerConsumption;
        }

        if (sumPowerConsumption > powerUnit.PeakLoad)
        {
            return new Success(false, "Disclaimer of warranty: The power supply unit may not withstand the load of the computer system", item);
        }

        return new Success(true, null, item);
    }
}