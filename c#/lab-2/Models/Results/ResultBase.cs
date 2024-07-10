namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

public abstract class ResultBase
{
    protected ResultBase(string? comment)
    {
        Comment = comment;
    }

    public string? Comment { get; private set; }
}