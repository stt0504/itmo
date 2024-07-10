namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public interface IComponent<T>
{
    public string Name { get; }
    public T Clone();
}