using System.Collections.Generic;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services;

public interface IRepository<T>
{
    public void AddComponent(T component);
    public T? GetComponent(string? name);

    public void DeleteComponent(string name);

    public void UpdateComponents(ICollection<T> components);
}