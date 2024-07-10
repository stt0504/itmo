namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Armor2 : ArmorBase
{
    public Armor2()
    {
        CurrentHitPoints = 50;
    }

    public override int MaxHitPoints => 50;

    public override int DamageFromAsteroid => 10;
    public override int DamageFromMeteorite => 25;
    public override int DamageFromCosmoWhales => 60;
    public override int DamageFromFlares => 0;
}