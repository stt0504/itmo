using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Models;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class SSD : IComponent<SSD>
{
    private SSD(string name, ConnectionType connectionType, int capacity, int maxSpeed, double powerConsumption)
    {
        Name = name;
        ConnectionType = connectionType;
        Capacity = capacity;
        MaxSpeed = maxSpeed;
        PowerConsumption = powerConsumption;
    }

    public string Name { get; private set; }
    public ConnectionType ConnectionType { get; private set; }
    public int Capacity { get; private set; }
    public int MaxSpeed { get; private set; }
    public double PowerConsumption { get; private set; }

    public SSD Clone()
    {
        return new SSD(
            Name,
            ConnectionType,
            Capacity,
            MaxSpeed,
            PowerConsumption);
    }

    public class Builder : IBuilder<SSD>
    {
        private ConnectionType _connectionType;
        private int _capacity;
        private int _maxSpeed;
        private double _powerConsumption;
        private string? _name;
        private Collection<IComponentValidator<SSD>> _validators;

        public Builder(Collection<IComponentValidator<SSD>> validators)
        {
            _validators = validators;
        }

        public Builder SetConnectionType(ConnectionType connectionType)
        {
            _connectionType = connectionType;
            return this;
        }

        public Builder SetCapacity(int capacity)
        {
            _capacity = capacity;
            return this;
        }

        public Builder SetMaxSpeed(int maxSpeed)
        {
            _maxSpeed = maxSpeed;
            return this;
        }

        public Builder SetPowerConsumption(double powerConsumption)
        {
            _powerConsumption = powerConsumption;
            return this;
        }

        public Builder SetName(string name)
        {
            _name = name;
            return this;
        }

        public SSD Build()
        {
            if (_name is null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            var ssd = new SSD(
                _name,
                _connectionType,
                _capacity,
                _maxSpeed,
                _powerConsumption);

            foreach (IComponentValidator<SSD> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(ssd);
                if (validationResult is not ValidComponent<SSD>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return ssd;
        }
    }
}