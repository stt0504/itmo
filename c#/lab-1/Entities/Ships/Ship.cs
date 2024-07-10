using System;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract class Ship
{
    protected Ship(ImpulseEngineBase engine, DeflectorBase? deflector, ArmorBase armorBase, JumpEngineBase? jumpEngine, AntinitrineEmitter? antinitrineEmitter)
    {
        ImpulseEngine = engine;
        Deflector = deflector;
        Armor = armorBase;
        JumpEngine = jumpEngine;
        AntinitrineEmitter = antinitrineEmitter;
        CrewIsAlive = true;
        IsWorking = true;
    }

    public ImpulseEngineBase ImpulseEngine { get; }
    public DeflectorBase? Deflector { get; }
    public ArmorBase Armor { get; }
    public JumpEngineBase? JumpEngine { get; }
    public AntinitrineEmitter? AntinitrineEmitter { get; }

    public bool CrewIsAlive { get; private set; }
    public bool IsWorking { get; private set; }

    public void Collide(ObstacleBase obstacle)
    {
        if (obstacle == null) throw new ArgumentNullException(nameof(obstacle));

        if (AntinitrineEmitter is not null && obstacle is CosmoWhales) return;

        if (Deflector is not null && Deflector.IsAlive)
        {
            Deflector.TakeDamage(obstacle);

            if (!Deflector.IsAlive)
            {
                Armor.TakeDamage(Deflector.CurrentHitPoints);
            }
        }
        else if (Armor.IsAlive)
        {
            Armor.TakeDamage(obstacle);
        }

        if (!Armor.IsAlive)
        {
            IsWorking = false;
        }

        if (!obstacle.DamageCrew) return;

        if (Deflector is null || Deflector.IsAlive == false || Deflector.FotonDeflectors == false)
        {
            CrewIsAlive = false;
        }
        else
        {
            Deflector.CatchFlare();
            const int maxFlaresAmount = 3;
            if (Deflector.FlaresCounter == maxFlaresAmount)
            {
                Deflector.Destruct();
            }
        }
    }
}