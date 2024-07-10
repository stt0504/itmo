namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Meredian : Ship
{
    public Meredian(bool fotonDeflectors)
        : base(
            new EngineE(),
            new DeflectorClass2(fotonDeflectors),
            new Armor2(),
            new JumpEngineGamma(),
            new AntinitrineEmitter())
    {
    }
}