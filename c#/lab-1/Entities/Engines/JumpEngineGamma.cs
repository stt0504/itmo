namespace Itmo.ObjectOrientedProgramming.Lab1;

public class JumpEngineGamma : JumpEngineBase
{
    private const int EngineGammaRange = 2000;

    public JumpEngineGamma()
        : base(EngineGammaRange)
    {
        CurrentFuel = 8000000;
    }

    public override int FuelSpendForKm => 400;

    public override int FuelConsumption(int distance)
    {
        CurrentFuel -= distance * distance * FuelSpendForKm;
        return distance * distance * FuelSpendForKm;
    }
}