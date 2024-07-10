using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Models;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class RAM : IComponent<RAM>
{
    private RAM(string name, int memorySize, string formFactor, DDRStandard ddrStandard, int powerConsumption)
    {
        Name = name;
        MemorySize = memorySize;
        FormFactor = formFactor;
        DDRStandard = ddrStandard;
        PowerConsumption = powerConsumption;
    }

    public string Name { get; private set; }
    public int MemorySize { get; private set; }

    public Collection<string> SupportedJEDECFrequencies { get; } =
        new();

    public Collection<string> XMPProfiles { get; } = new();
    public string FormFactor { get; private set; }
    public DDRStandard DDRStandard { get; private set; }
    public int PowerConsumption { get; private set; }

    public RAM Clone()
    {
        var clonedRam = new RAM(
            this.Name,
            this.MemorySize,
            this.FormFactor,
            this.DDRStandard,
            this.PowerConsumption);

        foreach (string frequency in SupportedJEDECFrequencies)
        {
            clonedRam.SupportedJEDECFrequencies.Add(frequency);
        }

        foreach (string profile in XMPProfiles)
        {
            clonedRam.XMPProfiles.Add(profile);
        }

        return clonedRam;
    }

    public class Builder : IBuilder<RAM>
    {
        private int _memorySize;
        private string? _name;
        private string? _formFactor;
        private DDRStandard _ddrStandard;
        private int _powerConsumption;
        private Collection<string> _supportedJEDECFrequencies = new();
        private Collection<string> _xmpProfiles = new();
        private Collection<IComponentValidator<RAM>> _validators;

        public Builder(Collection<IComponentValidator<RAM>> validators)
        {
            _validators = validators;
        }

        public Builder SetMemorySize(int memorySize)
        {
            _memorySize = memorySize;
            return this;
        }

        public Builder SetName(string name)
        {
            _name = name;
            return this;
        }

        public Builder SetFormFactor(string formFactor)
        {
            _formFactor = formFactor;
            return this;
        }

        public Builder SetDdrStandard(DDRStandard ddrStandard)
        {
            _ddrStandard = ddrStandard;
            return this;
        }

        public Builder SetPowerConsumption(int powerConsumption)
        {
            _powerConsumption = powerConsumption;
            return this;
        }

        public Builder AddSupportedJEDECFrequency(string frequency)
        {
            _supportedJEDECFrequencies.Add(frequency);
            return this;
        }

        public Builder AddXMPProfile(string profile)
        {
            _xmpProfiles.Add(profile);
            return this;
        }

        public RAM Build()
        {
            if (_name is null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            if (_formFactor is null)
            {
                throw new ArgumentNullException(nameof(_formFactor));
            }

            var ram = new RAM(
                _name,
                _memorySize,
                _formFactor,
                _ddrStandard,
                _powerConsumption);

            foreach (string frequency in _supportedJEDECFrequencies)
            {
                ram.SupportedJEDECFrequencies.Add(frequency);
            }

            foreach (string profile in _xmpProfiles)
            {
                ram.XMPProfiles.Add(profile);
            }

            foreach (IComponentValidator<RAM> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(ram);
                if (validationResult is not ValidComponent<RAM>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return ram;
        }
    }
}