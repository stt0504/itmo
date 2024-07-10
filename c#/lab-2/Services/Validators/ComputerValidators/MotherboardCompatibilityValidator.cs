using System;
using System.Collections.ObjectModel;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Models;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class MotherboardCompatibilityValidator : IComputerValidator
{
    public ComputerValidationResultBase Validate(Computer item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        Motherboard motherboard = item.Motherboard;
        CPU cpu = item.CPU;
        Collection<RAM> rams = item.RAM;
        WiFiAdapter? wiFiAdapter = item.WiFiAdapter;

        if (motherboard.Socket.Name != cpu.Socket.Name)
        {
            return new Failure("Error: The motherboard and processor are not compatible");
        }

        if (motherboard.RamSlotsNumber < rams.Count)
        {
            return new Failure("Error: There are not enough RAM slots on the motherboard");
        }

        if (!rams.All(ram => motherboard.SupportedDDRStandards.Contains(ram.DDRStandard)))
        {
            return new Failure("Error: The motherboard and RAM (or several of them) are incompatible");
        }

        int pcIeConnectionCount = 0;
        if (item.SSD is not null && item.SSD.ConnectionType == ConnectionType.PCIe)
        {
            pcIeConnectionCount++;
        }

        if (item.VideoCard is not null)
        {
            pcIeConnectionCount++;
        }

        if (pcIeConnectionCount > motherboard.PCIELinesCount)
        {
            return new Failure("Error: There are not enough PCI-E lines on the motherboard");
        }

        int sataConnectionCount = 0;
        if (item.SSD is not null && item.SSD.ConnectionType == ConnectionType.SATA)
        {
            sataConnectionCount++;
        }

        if (item.HDD is not null)
        {
            sataConnectionCount++;
        }

        if (sataConnectionCount > motherboard.SATAPortsCount)
        {
            return new Failure("Error: There are not enough SATA ports on the motherboard");
        }

        if (motherboard.BIOS.SupportedProcessors.All(supportedCPU => supportedCPU?.Name != cpu.Name))
        {
            return new Failure("Error: the BIOS does not support this processor");
        }

        if (motherboard.HasWifiAdapter && wiFiAdapter is not null)
        {
            return new Failure(
                "Error: Network equipment conflict: the motherboard already has a built-in Wi-Fi module");
        }

        return new Success(true, null, item);
    }
}