using System;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract class DeflectorBase
{
    protected DeflectorBase(bool fotonDeflectors)
    {
        FotonDeflectors = fotonDeflectors;
    }

    public abstract int MaxHitPoints { get; }
    public int CurrentHitPoints { get; protected set; }

    public abstract int DamageFromAsteroid { get; }
    public abstract int DamageFromMeteorite { get; }
    public abstract int DamageFromCosmoWhales { get; }
    public abstract int DamageFromFlares { get; }

    public bool FotonDeflectors { get; }
    public int FlaresCounter { get; private set; }

    public bool IsAlive => CurrentHitPoints > 0;

    public void CatchFlare()
    {
        FlaresCounter++;
    }

    public void TakeDamage(ObstacleBase obstacle)
    {
        if (obstacle is null)
        {
            throw new ArgumentNullException(nameof(obstacle));
        }

        CurrentHitPoints -= obstacle.DamageDeflector(this);
    }

    public void Destruct()
    {
        CurrentHitPoints = 0;
    }
}