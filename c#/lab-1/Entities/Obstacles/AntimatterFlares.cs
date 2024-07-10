using System;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public class AntimatterFlares : ObstacleBase
{
    public override bool DamageCrew => true;

    public override int DamageDeflector(DeflectorBase deflector)
    {
        if (deflector == null) throw new ArgumentNullException(nameof(deflector));
        return deflector.DamageFromFlares;
    }

    public override int DamageArmor(ArmorBase armor)
    {
        if (armor == null) throw new ArgumentNullException(nameof(armor));
        return armor.DamageFromFlares;
    }
}