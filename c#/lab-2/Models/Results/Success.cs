using Itmo.ObjectOrientedProgramming.Lab2.Entities;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

public class Success : ComputerValidationResultBase
{
    public Success(bool warranty, string? comment, Computer computer)
        : base(warranty, comment)
    {
        Computer = computer;
    }

    public Computer Computer { get; private set; }
}