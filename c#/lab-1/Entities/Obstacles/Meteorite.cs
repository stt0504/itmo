using System;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public class Meteorite : ObstacleBase
{
    public override bool DamageCrew => false;

    public override int DamageDeflector(DeflectorBase deflector)
    {
        if (deflector == null) throw new ArgumentNullException(nameof(deflector));
        return deflector.DamageFromMeteorite;
    }

    public override int DamageArmor(ArmorBase armor)
    {
        if (armor == null) throw new ArgumentNullException(nameof(armor));
        return armor.DamageFromMeteorite;
    }
}