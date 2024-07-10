namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract class ObstacleBase
{
    public abstract bool DamageCrew { get; }
    public abstract int DamageDeflector(DeflectorBase deflector);
    public abstract int DamageArmor(ArmorBase armor);
}