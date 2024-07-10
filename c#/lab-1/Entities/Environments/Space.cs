using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Space : EnvironmentBase
{
    public Space(Collection<ObstacleBase> obstacles)
        : base(obstacles)
    {
        if (!obstacles.All(obstacle => obstacle is SmallAsteroid or Meteorite))
        {
            throw new ArgumentException("Unacceptable obstacles in the environment Space");
        }
    }
}