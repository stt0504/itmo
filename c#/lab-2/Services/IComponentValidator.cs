using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services;

public interface IComponentValidator<T>
{
    public ResultBase Validate(T item);
}