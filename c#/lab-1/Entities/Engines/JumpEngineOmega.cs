namespace Itmo.ObjectOrientedProgramming.Lab1;

public class JumpEngineOmega : JumpEngineBase
{
    private const int EngineOmegaRange = 500;

    public JumpEngineOmega()
        : base(EngineOmegaRange)
    {
        CurrentFuel = 5000000;
    }

    public override int FuelSpendForKm => 200;

    public override int FuelConsumption(int distance)
    {
        CurrentFuel -= distance * int.Log2(distance) * FuelSpendForKm;
        return distance * int.Log2(distance) * FuelSpendForKm;
    }
}