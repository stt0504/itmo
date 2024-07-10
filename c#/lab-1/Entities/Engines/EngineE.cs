namespace Itmo.ObjectOrientedProgramming.Lab1;

public class EngineE : ImpulseEngineBase
{
    private const int EngineESpeed = 100;

    public EngineE()
        : base(EngineESpeed)
    {
        CurrentFuel = 300000;
    }

    public override double FuelStart => 3000;
    public override int FuelSpendForKm => 30;
}