namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Armor1 : ArmorBase
{
    public Armor1()
    {
        CurrentHitPoints = 25;
    }

    public override int MaxHitPoints => 25;

    public override int DamageFromAsteroid => 25;
    public override int DamageFromMeteorite => 30;
    public override int DamageFromCosmoWhales => 100;
    public override int DamageFromFlares => 0;
}