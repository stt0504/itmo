namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Success : PathResult
{
    public Success(double time, double fuelConsumed)
    {
        Time = time;
        FuelConsumed = fuelConsumed;
    }

    public double Time { get; }
    public double FuelConsumed { get; }
}