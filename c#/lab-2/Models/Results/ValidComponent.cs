namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

public class ValidComponent<T> : ResultBase
{
    public ValidComponent(T item)
        : base(null)
    {
        Item = item;
    }

    public T Item { get; private set; }
}