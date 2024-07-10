using System;
using System.Collections.ObjectModel;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests;

public class NitrineNebulaTest
{
    [Theory]
    [InlineData(typeof(Vaclas), typeof(ShipDestruction))]
    [InlineData(typeof(Augur), typeof(Success))]
    [InlineData(typeof(Meredian), typeof(Success))]
    public void TestNitrineNebula(Type shipType, Type resultType)
    {
        Ship? ship = null;

        if (shipType == typeof(Vaclas))
        {
            ship = new Vaclas(false);
        }
        else if (shipType == typeof(Augur))
        {
            ship = new Augur(false);
        }
        else if (shipType == typeof(Meredian))
        {
            ship = new Meredian(false);
        }

        var obstacles = new Collection<ObstacleBase> { new CosmoWhales() };
        var nitrineNebula = new NitrineParticlesNebula(obstacles);
        var pathSegment1 = new PathSegment(100, nitrineNebula);
        var path = new Path(new Collection<PathSegment> { pathSegment1 });

        if (ship == null) return;
        PathResult pathResult = path.TraverseRoute(ship);

        switch (ship)
        {
            case Augur:
                Assert.False(ship.Deflector?.IsAlive);
                Assert.True(ship.Armor.CurrentHitPoints == ship.Armor.MaxHitPoints);
                break;
            case Meredian:
                Assert.True(ship.Deflector?.CurrentHitPoints == ship.Deflector?.MaxHitPoints);
                break;
        }

        Assert.Equal(resultType, pathResult.GetType());
    }
}