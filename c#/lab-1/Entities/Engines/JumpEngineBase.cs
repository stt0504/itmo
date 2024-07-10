namespace Itmo.ObjectOrientedProgramming.Lab1;

public abstract class JumpEngineBase : EngineBase
{
    private const int JumpEngineSpeed = 0;

    protected JumpEngineBase(double range)
        : base(JumpEngineSpeed)
    {
        Range = range;
    }

    public double Range { get; private set; }
}