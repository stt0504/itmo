using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class VideoCard : IComponent<VideoCard>
{
    private VideoCard(string name, double length, double width, int videoMemorySize, string pcieVersion, double chipFrequency, int powerConsumption)
    {
        Name = name;
        Length = length;
        Width = width;
        VideoMemorySize = videoMemorySize;
        PCIeVersion = pcieVersion;
        ChipFrequency = chipFrequency;
        PowerConsumption = powerConsumption;
    }

    public string Name { get; private set; }
    public double Length { get; private set; }
    public double Width { get; private set; }
    public int VideoMemorySize { get; private set; }
    public string PCIeVersion { get; private set; }
    public double ChipFrequency { get; private set; }
    public int PowerConsumption { get; private set; }

    public VideoCard Clone()
    {
        return new VideoCard(
            Name,
            Length,
            Width,
            VideoMemorySize,
            PCIeVersion,
            ChipFrequency,
            PowerConsumption);
    }

    public class Builder : IBuilder<VideoCard>
    {
        private double _length;
        private double _width;
        private int _videoMemorySize;
        private string? _pciExpressVersion;
        private double _chipFrequency;
        private int _powerConsumption;
        private string? _name;
        private Collection<IComponentValidator<VideoCard>> _validators;

        public Builder(Collection<IComponentValidator<VideoCard>> validators)
        {
            _validators = validators;
        }

        public Builder SetLength(double length)
        {
            _length = length;
            return this;
        }

        public Builder SetWidth(double width)
        {
            _width = width;
            return this;
        }

        public Builder SetVideoMemorySize(int videoMemorySize)
        {
            _videoMemorySize = videoMemorySize;
            return this;
        }

        public Builder SetPciExpressVersion(string pciExpressVersion)
        {
            _pciExpressVersion = pciExpressVersion;
            return this;
        }

        public Builder SetChipFrequency(double chipFrequency)
        {
            _chipFrequency = chipFrequency;
            return this;
        }

        public Builder SetPowerConsumption(int powerConsumption)
        {
            _powerConsumption = powerConsumption;
            return this;
        }

        public Builder SetName(string name)
        {
            _name = name;
            return this;
        }

        public VideoCard Build()
        {
            if (_name is null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            if (_pciExpressVersion is null)
            {
                throw new ArgumentNullException(nameof(_pciExpressVersion));
            }

            var videoCard = new VideoCard(
                _name,
                _length,
                _width,
                _videoMemorySize,
                _pciExpressVersion,
                _chipFrequency,
                _powerConsumption);

            foreach (IComponentValidator<VideoCard> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(videoCard);
                if (validationResult is not ValidComponent<VideoCard>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return videoCard;
        }
    }
}