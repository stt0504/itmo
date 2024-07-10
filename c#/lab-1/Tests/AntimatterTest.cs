using System;
using System.Collections.ObjectModel;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests;

public class AntimatterTest
{
    [Theory]
    [InlineData(false, typeof(CrewLoss))]
    [InlineData(true, typeof(Success))]
    public void TestAntimatterFlare(bool fotonDeflectors, Type resultType)
    {
        Ship ship = new Vaclas(fotonDeflectors);

        var obstacles = new Collection<ObstacleBase> { new AntimatterFlares() };
        var channels = new Collection<SubspaceChannel>
            { new SubspaceChannel(10, obstacles) };
        var highDensityNebula = new HighDensityNebula(channels);
        var pathSegment1 = new PathSegment(10, highDensityNebula);
        var path = new Path(new Collection<PathSegment> { pathSegment1 });

        PathResult pathResult = path.TraverseRoute(ship);
        Assert.Equal(resultType, pathResult.GetType());
    }
}