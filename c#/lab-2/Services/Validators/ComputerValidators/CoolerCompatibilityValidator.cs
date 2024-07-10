using System;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class CoolerCompatibilityValidator : IComputerValidator
{
    public ComputerValidationResultBase Validate(Computer item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        CPUCoolingSystem cooler = item.Cooler;
        CPU cpu = item.CPU;

        if (cooler.SupportedSockets.All(supportedSocket => supportedSocket.Name != cpu.Socket.Name))
        {
            return new Failure("Error: the cooling system does not support the CPU socket");
        }

        if (cpu.HeatDissipation > cooler.MaxHeatDissipation)
        {
            return new Success(false, "Disclaimer of warranty: A weak cooling system has been selected for this processor", item);
        }

        return new Success(true, null, item);
    }
}