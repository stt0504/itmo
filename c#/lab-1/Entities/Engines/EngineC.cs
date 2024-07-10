namespace Itmo.ObjectOrientedProgramming.Lab1;

public class EngineC : ImpulseEngineBase
{
    private const int EngineCSpeed = 20;

    public EngineC()
        : base(EngineCSpeed)
    {
        CurrentFuel = 100000;
    }

    public override int FuelSpendForKm => 5;
    public override double FuelStart => 1000;

    public override int FuelConsumption(int distance)
    {
        return distance * FuelSpendForKm;
    }
}