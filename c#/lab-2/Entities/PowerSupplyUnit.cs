using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class PowerSupplyUnit : IComponent<PowerSupplyUnit>
{
    private PowerSupplyUnit(string name, int peakLoad)
    {
        Name = name;
        PeakLoad = peakLoad;
    }

    public string Name { get; private set; }
    public int PeakLoad { get; private set; }

    public PowerSupplyUnit Clone()
    {
        return new PowerSupplyUnit(Name, PeakLoad);
    }

    public class Builder : IBuilder<PowerSupplyUnit>
    {
        private int _peakLoad;
        private string? _name;
        private Collection<IComponentValidator<PowerSupplyUnit>> _validators;

        public Builder(Collection<IComponentValidator<PowerSupplyUnit>> validators)
        {
            _validators = validators;
        }

        public Builder SetPeakLoad(int peakLoad)
        {
            _peakLoad = peakLoad;
            return this;
        }

        public Builder SetName(string name)
        {
            _name = name;
            return this;
        }

        public PowerSupplyUnit Build()
        {
            if (_name is null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            var powerSupplyUnit = new PowerSupplyUnit(_name, _peakLoad);
            foreach (IComponentValidator<PowerSupplyUnit> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(powerSupplyUnit);
                if (validationResult is not ValidComponent<PowerSupplyUnit>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return powerSupplyUnit;
        }
    }
}