using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public class NitrineParticlesNebula : EnvironmentBase
{
    public NitrineParticlesNebula(Collection<ObstacleBase> obstacles)
        : base(obstacles)
    {
        if (!obstacles.All(obstacle => obstacle is CosmoWhales))
        {
            throw new ArgumentException("Unacceptable obstacles in the environment NitrineParticlesNebula");
        }
    }
}