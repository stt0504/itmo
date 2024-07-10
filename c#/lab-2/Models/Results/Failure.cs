namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

public class Failure : ComputerValidationResultBase
{
    public Failure(string? comment)
        : base(false, comment)
    {
    }
}