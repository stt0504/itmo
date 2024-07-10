namespace Itmo.ObjectOrientedProgramming.Lab1;

public class DeflectorClass2 : DeflectorBase
{
    public DeflectorClass2(bool fotonDeflectors)
        : base(fotonDeflectors)
    {
        CurrentHitPoints = 60;
    }

    public override int MaxHitPoints => 60;

    public override int DamageFromAsteroid => 6;
    public override int DamageFromMeteorite => 20;
    public override int DamageFromCosmoWhales => 170;
    public override int DamageFromFlares => 0;
}