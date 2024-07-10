namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

public abstract class ComputerValidationResultBase
{
    protected ComputerValidationResultBase(bool warranty, string? comment)
    {
        Comment = comment;
        Warranty = warranty;
    }

    public string? Comment { get; private set; }
    public bool Warranty { get; private set; }
}