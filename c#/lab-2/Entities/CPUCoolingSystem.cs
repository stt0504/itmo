using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Models;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class CPUCoolingSystem : IComponent<CPUCoolingSystem>
{
    private CPUCoolingSystem(string name, int length, int width, int height, Collection<Socket> supportedSockets, int maxHeatDissipation)
    {
        Name = name;
        Length = length;
        Width = width;
        Height = height;
        SupportedSockets = supportedSockets;
        MaxHeatDissipation = maxHeatDissipation;
    }

    public string Name { get; private set; }
    public int Length { get; private set; }
    public int Width { get; private set; }
    public int Height { get; private set; }
    public Collection<Socket> SupportedSockets { get; private set; }
    public int MaxHeatDissipation { get; private set; }

    public CPUCoolingSystem Clone()
    {
        var clonedCoolingSystem =
            new CPUCoolingSystem(Name, Length, Width, Height, SupportedSockets, MaxHeatDissipation);

        return clonedCoolingSystem;
    }

    public class Builder : IBuilder<CPUCoolingSystem>
    {
        private int _length;
        private int _width;
        private int _height;
        private Collection<Socket> _supportedSockets = new();
        private int _maxHeatDissipation;
        private string? _name;

        private Collection<IComponentValidator<CPUCoolingSystem>> _validators;

        public Builder(Collection<IComponentValidator<CPUCoolingSystem>> validators)
        {
            _validators = validators;
        }

        public Builder SetSize(int length, int width, int height)
        {
            _length = length;
            _width = width;
            _height = height;
            return this;
        }

        public Builder AddSupportedSockets(Collection<Socket> sockets)
        {
            _supportedSockets = sockets;
            return this;
        }

        public Builder SetMaxHeatDissipation(int maxHeatDissipation)
        {
            _maxHeatDissipation = maxHeatDissipation;
            return this;
        }

        public Builder SetName(string name)
        {
            _name = name;
            return this;
        }

        public CPUCoolingSystem Build()
        {
            if (_name == null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            var coolingSystem =
                new CPUCoolingSystem(_name, _length, _width, _height, _supportedSockets, _maxHeatDissipation);
            foreach (IComponentValidator<CPUCoolingSystem> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(coolingSystem);
                if (validationResult is not ValidComponent<CPUCoolingSystem>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return coolingSystem;
        }
    }
}