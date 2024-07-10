using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services;

namespace Itmo.ObjectOrientedProgramming.Lab2.Models;

public class Repository<T> : IRepository<T>
    where T : IComponent<T>
{
    private Collection<T> _components = new();
    public ReadOnlyCollection<T> Components => new(_components);

    public void AddComponent(T component)
    {
        _components.Add(component);
    }

    public T GetComponent(string? name)
    {
        T? res = _components.FirstOrDefault(component => component.Name == name);
        if (res == null)
        {
            throw new ArgumentNullException(nameof(name));
        }

        return res.Clone();
    }

    public void DeleteComponent(string name)
    {
        _components.Remove(_components.FirstOrDefault(component => component.Name == name) ?? throw new InvalidOperationException());
    }

    public void UpdateComponents(ICollection<T> components)
    {
        _components.Clear();
        if (components == null) return;
        foreach (T component in components)
        {
            AddComponent(component);
        }
    }
}