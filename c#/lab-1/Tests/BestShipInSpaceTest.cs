using System.Collections.ObjectModel;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests;

public class BestShipInSpaceTest
{
    [Fact]
    public void TestBestShipInSpace()
    {
        Ship ship1 = new Shuttle();
        Ship ship2 = new Vaclas(false);
        var obstacles = new Collection<ObstacleBase>();
        var space = new Space(obstacles);
        var pathSegment1 = new PathSegment(100, space);
        var path = new Path(new Collection<PathSegment> { pathSegment1 });

        Ship? result = path.BestShip(ship1, ship2);
        Assert.IsType<Shuttle>(result);
    }
}