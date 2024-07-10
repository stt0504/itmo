using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Models;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class CPU : IComponent<CPU>
{
    private CPU(string name, double coresFrequency, int coresCount, Socket socket, bool hasVideoCore, int memoryFrequency, int heatDissipation, int powerConsumption)
    {
        Name = name;
        CoresFrequency = coresFrequency;
        CoresCount = coresCount;
        Socket = socket;
        HasVideoCore = hasVideoCore;
        MemoryFrequency = memoryFrequency;
        HeatDissipation = heatDissipation;
        PowerConsumption = powerConsumption;
    }

    public string Name { get; private set; }
    public double CoresFrequency { get; private set; }
    public int CoresCount { get; private set; }
    public Socket Socket { get; private set; }
    public bool HasVideoCore { get; private set; }
    public int MemoryFrequency { get; private set; }
    public int HeatDissipation { get; private set; }
    public int PowerConsumption { get; private set; }

    public CPU Clone()
    {
        return new CPU(Name, CoresFrequency, CoresCount, Socket, HasVideoCore, MemoryFrequency, HeatDissipation, PowerConsumption);
    }

    public class Builder : IBuilder<CPU>
    {
        private double _coresFrequency;
        private int _coresCount;
        private Socket? _socket;
        private bool _hasVideoCore;
        private int _memoryFrequency;
        private int _heatDissipation;
        private int _powerConsumption;
        private string? _name;

        private Collection<IComponentValidator<CPU>> _validators;

        public Builder(Collection<IComponentValidator<CPU>> validators)
        {
            _validators = validators;
        }

        public Builder SetCoresFrequency(double frequency)
        {
            _coresFrequency = frequency;
            return this;
        }

        public Builder SetCoresCount(int count)
        {
            _coresCount = count;
            return this;
        }

        public Builder SetSocket(Socket socket)
        {
            _socket = socket;
            return this;
        }

        public Builder SetHasVideoCore(bool hasVideoCore)
        {
            _hasVideoCore = hasVideoCore;
            return this;
        }

        public Builder SetMemoryFrequency(int frequency)
        {
            _memoryFrequency = frequency;
            return this;
        }

        public Builder SetHeatDissipation(int heatDissipation)
        {
            _heatDissipation = heatDissipation;
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

        public CPU Build()
        {
            if (_name is null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            if (_socket is null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            var cpu = new CPU(_name, _coresFrequency, _coresCount, _socket, _hasVideoCore, _memoryFrequency, _heatDissipation, _powerConsumption);

            foreach (IComponentValidator<CPU> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(cpu);
                if (validationResult is not ValidComponent<CPU>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return cpu;
        }
    }
}