namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Vaclas : Ship
{
    public Vaclas(bool fotonDeflectors)
        : base(
            new EngineE(),
            new DeflectorClass1(fotonDeflectors),
            new Armor2(),
            new JumpEngineGamma(),
            null)
    {
    }
}