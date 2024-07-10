namespace Itmo.ObjectOrientedProgramming.Lab1;

public class DeflectorClass1 : DeflectorBase
{
    public DeflectorClass1(bool fotonDeflectors)
        : base(fotonDeflectors)
    {
        CurrentHitPoints = 30;
    }

    public override int MaxHitPoints => 30;

    public override int DamageFromAsteroid => 15;
    public override int DamageFromMeteorite => 30;
    public override int DamageFromCosmoWhales => 140;
    public override int DamageFromFlares => 0;
}