using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public class SubspaceChannel
{
    public SubspaceChannel(double length, Collection<ObstacleBase> obstacles)
    {
        if (!obstacles.All(obstacle => obstacle is AntimatterFlares))
        {
            throw new ArgumentException("Unacceptable obstacles in the subspace channel");
        }

        Obstacles = obstacles;
        Length = length;
    }

    public Collection<ObstacleBase> Obstacles { get; }
    public double Length { get; }
}