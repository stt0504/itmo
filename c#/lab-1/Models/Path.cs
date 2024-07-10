using System.Collections.ObjectModel;
using System.Linq;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Path
{
    public Path(Collection<PathSegment> pathSegments)
    {
        PathSegments = pathSegments;
    }

    public Collection<PathSegment> PathSegments { get; }

    public PathResult TraverseRoute(Ship ship)
    {
        double totalTime = 0;
        double totalFuelConsumed = 0;

        foreach (PathSegment segment in PathSegments)
        {
            double segmentTime = 0;
            double segmentFuelConsumed = 0;
            PathResult result = segment.CalculateTravel(ship, ref segmentTime, ref segmentFuelConsumed);
            if (result is not Success)
            {
                return result;
            }

            totalTime += segmentTime;
            totalFuelConsumed += segmentFuelConsumed;
        }

        return new Success(totalTime, totalFuelConsumed);
    }

    public Ship? BestShip(Ship ship1, Ship ship2)
    {
        PathResult result1 = TraverseRoute(ship1);
        PathResult result2 = TraverseRoute(ship2);

        if (result1 is not Success && result2 is not Success) return null;

        if (result1 is not Success success1) return ship2;
        if (result2 is not Success success2) return ship1;
        if (!PathSegments.Any(segment => segment.Environment is NitrineParticlesNebula))
            return success1.FuelConsumed < success2.FuelConsumed ? ship1 : ship2;

        if (ship1?.ImpulseEngine is EngineC && ship2?.ImpulseEngine is EngineE)
        {
            return ship2;
        }

        if (ship2?.ImpulseEngine is EngineC && ship1?.ImpulseEngine is EngineE)
        {
            return ship1;
        }

        return success1.FuelConsumed < success2.FuelConsumed ? ship1 : ship2;
    }
}