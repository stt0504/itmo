using System;
using System.Collections.ObjectModel;
using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.MemoryFileSystemComponents;

namespace Itmo.ObjectOrientedProgramming.Lab4.Models;

public class Path
{
    public Path(string path)
    {
        if (string.IsNullOrWhiteSpace(path)) throw new ArgumentException("Path cannot be null or empty", nameof(path));

        Components = new Collection<string>(path.Split(System.IO.Path.DirectorySeparatorChar));
    }

    public Collection<string> Components { get; }

    public IFileSystemComponent GetFileSystemComponent(IFileSystemComponent root)
    {
        if (root is null) throw new ArgumentNullException(nameof(root));
        IFileSystemComponent currentComponent = root;

        if (Components.Count == 1 && Components[0] != root.Name) throw new ArgumentException("No such component found");
        for (int i = 1; i < Components.Count; i++)
        {
            if (currentComponent is InMemoryCatalog currentCatalog &&
                currentCatalog.Components.FirstOrDefault(component => component.Name == Components[i]) is not null)
            {
                currentComponent = currentCatalog.Components.First(component => component.Name == Components[i]);
            }
            else if (currentComponent.Name != Components[^1])
            {
                throw new ArgumentException("No such component found");
            }
        }

        return currentComponent;
    }

    public void SetFileSystemComponent(IFileSystemComponent root, IFileSystemComponent newComponent)
    {
        if (root is null) throw new ArgumentNullException(nameof(root));
        IFileSystemComponent currentComponent = root;

        for (int i = 1; i < Components.Count - 1; i++)
        {
            if (currentComponent is InMemoryCatalog currentFolder &&
                currentFolder.Components.FirstOrDefault(component => component.Name == Components[i]) is not null)
            {
                currentComponent = currentFolder.Components.First(component => component.Name == Components[i]);
            }
            else
            {
                throw new ArgumentException("No such component found");
            }
        }

        if (currentComponent is InMemoryCatalog catalog)
        {
            if (newComponent is null) throw new ArgumentNullException(nameof(newComponent));
            catalog.Components.Add(newComponent);
        }
    }

    public void DeleteFile(IFileSystemComponent root)
    {
        IFileSystemComponent component = GetFileSystemComponent(root);
        if (component is null) throw new ArgumentException("component is null");

        component.Delete();
    }
}