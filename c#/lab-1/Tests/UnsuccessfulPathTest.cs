using System;
using System.Collections.ObjectModel;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests;

public class UnsuccessfulPathTest
{
    [Theory]
    [InlineData(typeof(Shuttle), typeof(ShipLoss))]
    [InlineData(typeof(Augur), typeof(ShipLoss))]
    public void TestUnsuccessfulRoute(Type shipType, Type resultType)
    {
        Ship? ship = null;

        if (shipType == typeof(Shuttle))
        {
            ship = new Shuttle();
        }
        else if (shipType == typeof(Augur))
        {
            ship = new Augur(false);
        }

        var obstacles = new Collection<ObstacleBase>();
        var channels = new Collection<SubspaceChannel>
            { new SubspaceChannel(100, obstacles), new SubspaceChannel(200, obstacles) };
        var highDensityNebula = new HighDensityNebula(channels);
        var pathSegment1 = new PathSegment(300, highDensityNebula);
        var path = new Path(new Collection<PathSegment> { pathSegment1 });
        if (ship == null) return;

        PathResult pathResult = path.TraverseRoute(ship);
        Assert.Equal(resultType, pathResult.GetType());
    }
}