using System.Collections.ObjectModel;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests;

public class ParticlesNebulaTest
{
    [Fact]
    public void TestParticlesNebula()
    {
        Ship ship1 = new Shuttle();
        Ship ship2 = new Vaclas(false);
        var nitrineParticlesNebula = new NitrineParticlesNebula(new Collection<ObstacleBase>());
        var pathSegment1 = new PathSegment(600, nitrineParticlesNebula);
        var path = new Path(new Collection<PathSegment> { pathSegment1 });

        Ship? result = path.BestShip(ship1, ship2);
        Assert.IsType<Vaclas>(result);
    }
}