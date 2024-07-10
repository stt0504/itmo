using System;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract class ArmorBase
{
    public abstract int MaxHitPoints { get; }
    public int CurrentHitPoints { get; protected set; }
    public abstract int DamageFromAsteroid { get; }
    public abstract int DamageFromMeteorite { get; }
    public abstract int DamageFromCosmoWhales { get; }
    public abstract int DamageFromFlares { get; }
    public bool IsAlive => CurrentHitPoints > 0;

    public void TakeDamage(ObstacleBase obstacle)
    {
        if (obstacle is null)
        {
            throw new ArgumentNullException(nameof(obstacle));
        }

        CurrentHitPoints -= obstacle.DamageArmor(this);
    }

    public void TakeDamage(int damage)
    {
        if (damage > 0)
        {
            throw new ArgumentException("Damage must be <= 0", nameof(damage));
        }

        CurrentHitPoints += damage;
    }
}