using System;
using System.Linq;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public class PathSegment
{
    public PathSegment(int distance, EnvironmentBase environment)
    {
        Distance = distance;
        Environment = environment;
    }

    public int Distance { get; }
    public EnvironmentBase Environment { get; }

    public PathResult CalculateTravel(Ship ship, ref double time, ref double fuel)
    {
        if (ship == null) throw new ArgumentNullException(nameof(ship));

        switch (Environment)
        {
            case Space or NitrineParticlesNebula:
                foreach (ObstacleBase obstacle in Environment.Obstacles)
                {
                    ship.Collide(obstacle);
                    if (ship.CrewIsAlive == false)
                    {
                        return new CrewLoss();
                    }

                    if (ship.IsWorking == false)
                    {
                        return new ShipDestruction();
                    }
                }

                time = Distance / ship.ImpulseEngine.Speed;
                fuel = ship.ImpulseEngine.FuelStart + ship.ImpulseEngine.FuelConsumption(Distance);

                if (ship.ImpulseEngine.CurrentFuel <= 0)
                {
                    return new ShipLoss();
                }

                break;

            case HighDensityNebula nebula:
                if (ship.JumpEngine is null)
                {
                    return new ShipLoss();
                }

                foreach (ObstacleBase obstacle in Environment.Obstacles)
                {
                    ship.Collide(obstacle);
                    if (ship.CrewIsAlive == false)
                    {
                        return new CrewLoss();
                    }

                    if (ship.IsWorking == false)
                    {
                        return new ShipDestruction();
                    }
                }

                if (nebula.SubspaceChannels.Any(channel => channel.Length > ship.JumpEngine.Range))
                {
                    return new ShipLoss();
                }

                time = 0;
                fuel = ship.JumpEngine.FuelConsumption(Distance);
                if (ship.JumpEngine.CurrentFuel <= 0)
                {
                    return new ShipLoss();
                }

                break;

            default:
                return new ShipLoss();
        }

        return new Success(time, fuel);
    }
}