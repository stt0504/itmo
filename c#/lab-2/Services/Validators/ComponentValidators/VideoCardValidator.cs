using System;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

public class VideoCardValidator : IComponentValidator<VideoCard>
{
    public ResultBase Validate(VideoCard item)
    {
        if (item == null) throw new ArgumentNullException(nameof(item));

        if (item.Length <= 0)
        {
            return new InvalidComponent<VideoCard>("Invalid Videocard Length");
        }

        if (item.Width <= 0)
        {
            return new InvalidComponent<VideoCard>("Invalid Videocard Width");
        }

        if (item.VideoMemorySize <= 0)
        {
            return new InvalidComponent<VideoCard>("Invalid Videocard Video Memory Size");
        }

        if (item.ChipFrequency <= 0)
        {
            return new InvalidComponent<VideoCard>("Invalid Videocard Chip Frequency");
        }

        if (item.PowerConsumption <= 0)
        {
            return new InvalidComponent<VideoCard>("Invalid Videocard Power Consumption");
        }

        return new ValidComponent<VideoCard>(item);
    }
}