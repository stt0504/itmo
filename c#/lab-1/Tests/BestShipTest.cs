using System.Collections.ObjectModel;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests;

public class BestShipTest
{
    [Fact]
    public void MyTest()
    {
        var obstacles1 = new Collection<ObstacleBase> { new CosmoWhales() };
        var obstacles2 = new Collection<ObstacleBase>();
        var obstacles3 = new Collection<ObstacleBase> { new AntimatterFlares() };
        var channel1 = new SubspaceChannel(100, obstacles3);
        var channels = new Collection<SubspaceChannel> { channel1 };

        var space = new Space(obstacles2);
        var highDensityNebula = new HighDensityNebula(channels);
        var nitrineParticlesNebula = new NitrineParticlesNebula(obstacles1);

        var pathSegment1 = new PathSegment(200, space);
        var pathSegment2 = new PathSegment(100, highDensityNebula);
        var pathSegment3 = new PathSegment(300, nitrineParticlesNebula);

        var path = new Path(new Collection<PathSegment> { pathSegment1, pathSegment2, pathSegment3 });

        var ship1 = new Augur(true);
        var ship2 = new Vaclas(false);

        Ship? result = path.BestShip(ship1, ship2);
        Assert.IsType<Augur>(result);
    }
}