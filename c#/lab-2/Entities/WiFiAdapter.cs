using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class WiFiAdapter : IComponent<WiFiAdapter>
{
    private WiFiAdapter(string name, string wifiStandardVersion, bool hasBluetooth, string pcieVersion, int powerConsumption)
    {
        Name = name;
        WiFiStandardVersion = wifiStandardVersion;
        HasBluetooth = hasBluetooth;
        PCIEVersion = pcieVersion;
        PowerConsumption = powerConsumption;
    }

    public string Name { get; private set; }
    public string WiFiStandardVersion { get; private set; }
    public bool HasBluetooth { get; private set; }
    public string PCIEVersion { get; private set; }
    public int PowerConsumption { get; private set; }

    public WiFiAdapter Clone()
    {
        return new WiFiAdapter(
            Name,
            WiFiStandardVersion,
            HasBluetooth,
            PCIEVersion,
            PowerConsumption);
    }

    public class Builder : IBuilder<WiFiAdapter>
    {
        private string? _wiFiStandardVersion;
        private bool _hasBluetooth;
        private string? _pcieVersion;
        private int _powerConsumption;
        private string? _name;
        private Collection<IComponentValidator<WiFiAdapter>> _validators;

        public Builder(Collection<IComponentValidator<WiFiAdapter>> validators)
        {
            _validators = validators;
        }

        public Builder SetWiFiStandardVersion(string wiFiStandardVersion)
        {
            _wiFiStandardVersion = wiFiStandardVersion;
            return this;
        }

        public Builder SetHasBluetooth(bool hasBluetooth)
        {
            _hasBluetooth = hasBluetooth;
            return this;
        }

        public Builder SetPCIEVersion(string pcieVersion)
        {
            _pcieVersion = pcieVersion;
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

        public WiFiAdapter Build()
        {
            if (_name == null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            if (_wiFiStandardVersion == null)
            {
                throw new ArgumentNullException(nameof(_wiFiStandardVersion));
            }

            if (_pcieVersion == null)
            {
                throw new ArgumentNullException(nameof(_pcieVersion));
            }

            var wiFiAdapter = new WiFiAdapter(
                _name,
                _wiFiStandardVersion,
                _hasBluetooth,
                _pcieVersion,
                _powerConsumption);

            foreach (IComponentValidator<WiFiAdapter> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(wiFiAdapter);
                if (validationResult is not ValidComponent<WiFiAdapter>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return wiFiAdapter;
        }
    }
}