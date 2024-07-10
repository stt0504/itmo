using System.Collections.ObjectModel;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests;

public class HighDensityNebulaTest
{
    [Fact]
    public void TestHighDensityNebula()
    {
        Ship ship1 = new Augur(false);
        Ship ship2 = new Stella(false);
        var channel1 = new SubspaceChannel(100, new Collection<ObstacleBase>());
        var channel2 = new SubspaceChannel(500, new Collection<ObstacleBase>());
        var channels = new Collection<SubspaceChannel> { channel1, channel2 };
        var highDensityNebula = new HighDensityNebula(channels);
        var pathSegment1 = new PathSegment(600, highDensityNebula);
        var path = new Path(new Collection<PathSegment> { pathSegment1 });

        Ship? result = path.BestShip(ship1, ship2);
        Assert.IsType<Stella>(result);
    }
}