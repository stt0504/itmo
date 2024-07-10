using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class Computer
{
    private Computer(CPU cpu, CPUCoolingSystem cooler, Motherboard motherboard, PowerSupplyUnit powerSupplyUnit, Collection<RAM> ram, SystemCase systemCase)
    {
        CPU = cpu;
        Cooler = cooler;
        Motherboard = motherboard;
        PowerSupplyUnit = powerSupplyUnit;
        RAM = ram;
        SystemCase = systemCase;
    }

    public bool Warranty { get; private set; } = true;
    public string? Comment { get; private set; }
    public CPU CPU { get; private set; }
    public CPUCoolingSystem Cooler { get; private set; }
    public HDD? HDD { get; private set; }
    public Motherboard Motherboard { get; private set; }
    public PowerSupplyUnit PowerSupplyUnit { get; private set; }
    public Collection<RAM> RAM { get; private set; }
    public SSD? SSD { get; private set; }
    public SystemCase SystemCase { get; private set; }
    public VideoCard? VideoCard { get; private set; }
    public WiFiAdapter? WiFiAdapter { get; private set; }

    public Computer Clone()
    {
        var clonedComputer = new Computer(CPU, Cooler, Motherboard, PowerSupplyUnit, RAM, SystemCase)
        {
            HDD = HDD,
            SSD = SSD,
            VideoCard = VideoCard,
            WiFiAdapter = WiFiAdapter,
        };
        return clonedComputer;
    }

    public class Builder : IBuilder<Computer>
    {
        private CPU? _cpu;
        private CPUCoolingSystem? _cooler;
        private HDD? _hdd;
        private Motherboard? _motherboard;
        private PowerSupplyUnit? _powerSupplyUnit;
        private Collection<RAM> _ram = new();
        private SSD? _ssd;
        private SystemCase? _systemCase;
        private VideoCard? _videoCard;
        private WiFiAdapter? _wiFiAdapter;

        private Collection<IComputerValidator
        > _validators;

        public Builder(Collection<IComputerValidator> validators)
        {
            _validators = validators;
        }

        public Builder SetCPU(CPU cpu)
        {
            _cpu = cpu;
            return this;
        }

        public Builder SetCooler(CPUCoolingSystem cooler)
        {
            _cooler = cooler;
            return this;
        }

        public Builder SetHDD(HDD hdd)
        {
            _hdd = hdd;
            return this;
        }

        public Builder SetMotherboard(Motherboard motherboard)
        {
            _motherboard = motherboard;
            return this;
        }

        public Builder SetPowerUnit(PowerSupplyUnit powerSupplyUnit)
        {
            _powerSupplyUnit = powerSupplyUnit;
            return this;
        }

        public Builder SetRAM(RAM ram)
        {
            _ram.Add(ram);
            return this;
        }

        public Builder SetSSD(SSD ssd)
        {
            _ssd = ssd;
            return this;
        }

        public Builder SetSystemCase(SystemCase systemCase)
        {
            _systemCase = systemCase;
            return this;
        }

        public Builder SetVideoCard(VideoCard videoCard)
        {
            _videoCard = videoCard;
            return this;
        }

        public Builder SetWifiAdapter(WiFiAdapter wiFiAdapter)
        {
            _wiFiAdapter = wiFiAdapter;
            return this;
        }

        public Computer Build()
        {
            if (_cpu is null)
            {
                throw new ArgumentNullException(nameof(_cpu));
            }

            if (_cooler is null)
            {
                throw new ArgumentNullException(nameof(_cooler));
            }

            if (_motherboard is null)
            {
                throw new ArgumentNullException(nameof(_motherboard));
            }

            if (_powerSupplyUnit is null)
            {
                throw new ArgumentNullException(nameof(_powerSupplyUnit));
            }

            if (_systemCase is null)
            {
                throw new ArgumentNullException(nameof(_systemCase));
            }

            var computer = new Computer(_cpu, _cooler, _motherboard, _powerSupplyUnit, _ram, _systemCase)
            {
                HDD = _hdd,
                SSD = _ssd,
                VideoCard = _videoCard,
                WiFiAdapter = _wiFiAdapter,
            };

            foreach (IComputerValidator validator in _validators)
            {
                if (validator.Validate(computer).Warranty == false)
                {
                    computer.Warranty = false;
                }

                if (validator.Validate(computer).Comment is not null)
                {
                    computer.Comment += validator.Validate(computer).Comment + "\n";
                }

                if (validator.Validate(computer) is not Success)
                {
                    throw new ArgumentException(computer.Comment);
                }
            }

            return computer;
        }
    }
}