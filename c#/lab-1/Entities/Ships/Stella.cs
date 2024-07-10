namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Stella : Ship
{
    public Stella(bool fotonDeflectors)
        : base(
            new EngineC(),
            new DeflectorClass1(fotonDeflectors),
            new Armor1(),
            new JumpEngineOmega(),
            null)
    {
    }
}