namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Armor3 : ArmorBase
{
    public Armor3()
    {
        CurrentHitPoints = 100;
    }

    public override int MaxHitPoints => 100;

    public override int DamageFromAsteroid => 5;
    public override int DamageFromMeteorite => 20;
    public override int DamageFromCosmoWhales => 110;
    public override int DamageFromFlares => 0;
}