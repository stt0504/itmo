namespace Itmo.ObjectOrientedProgramming.Lab2.Services;

public interface IFactory<T>
{
    public T? Create(string? name);
}