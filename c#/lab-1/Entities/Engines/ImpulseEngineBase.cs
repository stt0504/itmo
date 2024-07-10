namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract class ImpulseEngineBase : EngineBase
{
    protected ImpulseEngineBase(int speed)
        : base(speed)
    {
    }

    public abstract double FuelStart { get; }
}