using System;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;
using Itmo.ObjectOrientedProgramming.Lab4.Services.Traversal;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.Printer;

public class ConsolePrinter : IPrinter
{
    public ConsolePrinter(ICatalogTraversal traversal)
    {
        Traversal = traversal;
    }

    public ICatalogTraversal Traversal { get; }

    public void PrintFile(IFile file)
    {
        if (file is null) throw new ArgumentNullException(nameof(file));
        Console.WriteLine(file.Name);
        Console.WriteLine(file.Data);
    }

    public void PrintCatalog(IFileSystemComponent root, int depth)
    {
        IFileSystemComponent rootToPrint = Traversal.Traverse(root);
        string indent = string.Empty;
        bool isLast = true;
        PrintCatalogUtility(rootToPrint, indent, isLast, depth);
    }

    private void PrintCatalogUtility(IFileSystemComponent root, string indent, bool isLast, int depth)
    {
        if (depth == 0) return;

        Console.Write(indent);

        if (isLast)
        {
            Console.Write('\\');
            indent += "  ";
        }
        else
        {
            Console.Write("|-");
            indent += "| ";
        }

        if (root is null) throw new ArgumentNullException(nameof(root));
        Console.WriteLine(root.Name);

        if (root is not ICatalog catalog) return;
        for (int i = 0; i < catalog.Components.Count; i++)
        {
            PrintCatalogUtility(catalog.Components[i], indent, i == catalog.Components.Count - 1, depth - 1);
        }
    }
}