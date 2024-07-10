namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Results;
public class InvalidComponent<T> : ResultBase
{
    public InvalidComponent(string? comment)
        : base(comment) { }
}