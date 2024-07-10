namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Shuttle : Ship
{
    public Shuttle()
        : base(
            new EngineC(),
            null,
            new Armor1(),
            null,
            null)
    {
    }
}