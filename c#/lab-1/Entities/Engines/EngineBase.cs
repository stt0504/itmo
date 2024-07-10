namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract class EngineBase
{
    protected EngineBase(int speed)
    {
        Speed = speed;
    }

    public int Speed { get; }
    public int CurrentFuel { get; protected set; }
    public abstract int FuelSpendForKm { get; }

    public virtual int FuelConsumption(int distance)
    {
        CurrentFuel -= distance * FuelSpendForKm;
        return distance * FuelSpendForKm;
    }
}