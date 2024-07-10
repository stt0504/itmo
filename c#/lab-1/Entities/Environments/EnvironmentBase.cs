using System.Collections.ObjectModel;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract class EnvironmentBase
{
    protected EnvironmentBase(Collection<ObstacleBase> obstacles)
    {
        Obstacles = obstacles;
    }

    public Collection<ObstacleBase> Obstacles { get; }
}