using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class HDD : IComponent<HDD>
{
    private HDD(string name, int capacity, int spindleSpeed, int powerConsumption)
    {
        Name = name;
        Capacity = capacity;
        SpindleSpeed = spindleSpeed;
        PowerConsumption = powerConsumption;
    }

    public string Name { get; private set; }
    public int Capacity { get; private set; }
    public int SpindleSpeed { get; private set; }
    public int PowerConsumption { get; private set; }

    public HDD Clone()
    {
        return new HDD(Name, Capacity, SpindleSpeed, PowerConsumption);
    }

    public class Builder : IBuilder<HDD>
    {
        private int _capacity;
        private int _spindleSpeed;
        private int _powerConsumption;
        private string? _name;

        private Collection<IComponentValidator<HDD>> _validators;

        public Builder(Collection<IComponentValidator<HDD>> validators)
        {
            _validators = validators;
        }

        public Builder SetCapacity(int capacity)
        {
            _capacity = capacity;
            return this;
        }

        public Builder SetSpindleSpeed(int spindleSpeed)
        {
            _spindleSpeed = spindleSpeed;
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

        public HDD Build()
        {
            if (_name == null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            var hdd = new HDD(_name, _capacity, _spindleSpeed, _powerConsumption);

            foreach (IComponentValidator<HDD> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(hdd);
                if (validationResult is not ValidComponent<HDD>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return hdd;
        }
    }
}