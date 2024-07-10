namespace Itmo.ObjectOrientedProgramming.Lab1;

public class DeflectorClass3 : DeflectorBase
{
    public DeflectorClass3(bool fotonDeflectors)
        : base(fotonDeflectors)
    {
        CurrentHitPoints = 120;
    }

    public override int MaxHitPoints => 120;

    public override int DamageFromAsteroid => 3;
    public override int DamageFromMeteorite => 12;
    public override int DamageFromCosmoWhales => 120;
    public override int DamageFromFlares => 0;
}