using System.Collections.ObjectModel;
using System.Linq;

namespace Itmo.ObjectOrientedProgramming.Lab1;

public class HighDensityNebula : EnvironmentBase
{
    public HighDensityNebula(Collection<SubspaceChannel> subspaceChannels)
        : base(new Collection<ObstacleBase>(
            subspaceChannels.SelectMany(channel => channel.Obstacles).ToList()))
    {
        SubspaceChannels = subspaceChannels;
    }

    public Collection<SubspaceChannel> SubspaceChannels { get; }
}