using System;
using System.IO;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents;
using Itmo.ObjectOrientedProgramming.Lab4.Entities.FileSystemComponents.LocalFileSystemComponents;

namespace Itmo.ObjectOrientedProgramming.Lab4.Services.FileSystemStrategy;

public class LocalFileSystemStrategy : IFileSystemStrategy
{
    public void CopyFile(string sourcePath, string destinationPath)
    {
        if (!File.Exists(sourcePath))
        {
            throw new ArgumentException("incorrect source path");
        }

        if (!File.Exists(destinationPath))
        {
            throw new ArgumentException("incorrect destination path");
        }

        File.Copy(sourcePath, destinationPath, true);
    }

    public void DeleteFile(string path)
    {
        if (!File.Exists(path))
        {
            throw new ArgumentException("incorrect path");
        }

        File.Delete(path);
    }

    public IFileSystemComponent GetComponent(string path)
    {
        if (path is null) throw new ArgumentNullException(nameof(path));

        if (Directory.Exists(path))
        {
            var catalog = new LocalCatalog(path.Split('\\')[^1], path);

            string[] files = Directory.GetFiles(path);
            foreach (string file in files)
            {
                catalog.Components.Add(new LocalFile(file.Split('\\')[^1], file));
            }

            string[] directories = Directory.GetDirectories(path);
            foreach (string directory in directories)
            {
                catalog.Components.Add(GetComponent(directory));
            }

            return catalog;
        }

        var resultFile = new LocalFile(path.Split('\\')[^1], path);
        resultFile.Data = File.ReadAllText(path);
        return resultFile;
    }
}