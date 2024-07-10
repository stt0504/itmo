namespace Itmo.ObjectOrientedProgramming.Lab1;

public class JumpEngineAlpha : JumpEngineBase
{
    private const int EngineAlphaRange = 100;

    public JumpEngineAlpha()
        : base(EngineAlphaRange)
    {
        CurrentFuel = 1000000;
    }

    public override int FuelSpendForKm => 100;

    public override int FuelConsumption(int distance)
    {
        CurrentFuel -= distance * FuelSpendForKm;
        return distance * FuelSpendForKm;
    }
}