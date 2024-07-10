using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Models;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services;

public class ComponentFactory<T> : IFactory<T>
    where T : IComponent<T>
{
    private readonly Repository<T> _repository;

    public ComponentFactory(Repository<T> repository)
    {
        _repository = repository;
    }

    public T? Create(string? name)
    {
        return _repository.GetComponent(name);
    }
}
