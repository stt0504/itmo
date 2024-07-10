namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Augur : Ship
{
    public Augur(bool fotonDeflectors)
        : base(
            new EngineE(),
            new DeflectorClass3(fotonDeflectors),
            new Armor3(),
            new JumpEngineAlpha(),
            null)
    {
    }
}