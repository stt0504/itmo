using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Models;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Results;

namespace Itmo.ObjectOrientedProgramming.Lab2.Entities;

public class Motherboard : IComponent<Motherboard>
{
    private Motherboard(string name, Socket socket, FormFactor formFactor, BIOS bios, int pciExpressLinesCount, int sataPortsCount, Chipset chipset, int ramSlotsNumber, bool hasWifiAdapter, Collection<DDRStandard> supportedDDRStandards)
    {
        Name = name;
        Socket = socket;
        FormFactor = formFactor;
        BIOS = bios;
        PCIELinesCount = pciExpressLinesCount;
        SATAPortsCount = sataPortsCount;
        Chipset = chipset;
        RamSlotsNumber = ramSlotsNumber;
        HasWifiAdapter = hasWifiAdapter;
        SupportedDDRStandards = supportedDDRStandards;
    }

    public string Name { get; private set; }
    public Socket Socket { get; private set; }
    public FormFactor FormFactor { get; private set; }
    public BIOS BIOS { get; private set; }
    public int PCIELinesCount { get; private set; }
    public int SATAPortsCount { get; private set; }
    public Chipset Chipset { get; private set; }
    public int RamSlotsNumber { get; private set; }
    public bool HasWifiAdapter { get; private set; }
    public Collection<DDRStandard> SupportedDDRStandards { get; private set; }

    public Motherboard Clone()
    {
        var clonedMotherboard = new Motherboard(
            Name,
            Socket,
            FormFactor,
            BIOS,
            PCIELinesCount,
            SATAPortsCount,
            Chipset,
            RamSlotsNumber,
            HasWifiAdapter,
            new Collection<DDRStandard>(SupportedDDRStandards));

        return clonedMotherboard;
    }

    public class Builder : IBuilder<Motherboard>
    {
        private Socket? _socket;
        private FormFactor _formFactor;
        private BIOS? _bios;
        private int _pcieLinesCount;
        private int _sataPortsCount;
        private Chipset? _chipset;
        private int _ramSlotsNumber;
        private bool _hasWifiAdapter;
        private Collection<DDRStandard> _supportedDdrStandards = new();
        private string? _name;
        private Collection<IComponentValidator<Motherboard>> _validators;

        public Builder(Collection<IComponentValidator<Motherboard>> validators)
        {
            _validators = validators;
        }

        public Builder SetSocket(Socket socket)
        {
            _socket = socket;
            return this;
        }

        public Builder SetFormFactor(FormFactor formFactor)
        {
            _formFactor = formFactor;
            return this;
        }

        public Builder SetBIOS(BIOS bios)
        {
            _bios = bios;
            return this;
        }

        public Builder SetPcieLinesCount(int pcieLinesCount)
        {
            _pcieLinesCount = pcieLinesCount;
            return this;
        }

        public Builder SetSataPortsCount(int sataPortsCount)
        {
            _sataPortsCount = sataPortsCount;
            return this;
        }

        public Builder SetChipset(Chipset? chipset)
        {
            _chipset = chipset;
            return this;
        }

        public Builder SetRamSlotsNumber(int ramSlotsNumber)
        {
            _ramSlotsNumber = ramSlotsNumber;
            return this;
        }

        public Builder SetWifiAdapter()
        {
            _hasWifiAdapter = true;
            return this;
        }

        public Builder AddSupportedDdrStandard(DDRStandard ddrStandard)
        {
            _supportedDdrStandards.Add(ddrStandard);
            return this;
        }

        public Builder SetName(string name)
        {
            _name = name;
            return this;
        }

        public Motherboard Build()
        {
            if (_name is null)
            {
                throw new ArgumentNullException(nameof(_name));
            }

            if (_socket is null)
            {
                throw new ArgumentNullException(nameof(_socket));
            }

            if (_bios is null)
            {
                throw new ArgumentNullException(nameof(_bios));
            }

            if (_chipset is null)
            {
                throw new ArgumentNullException(nameof(_chipset));
            }

            var motherboard = new Motherboard(
                _name,
                _socket,
                _formFactor,
                _bios,
                _pcieLinesCount,
                _sataPortsCount,
                _chipset,
                _ramSlotsNumber,
                _hasWifiAdapter,
                _supportedDdrStandards);

            foreach (IComponentValidator<Motherboard> validator in _validators)
            {
                ResultBase validationResult = validator.Validate(motherboard);
                if (validationResult is not ValidComponent<Motherboard>)
                {
                    throw new ArgumentException(validationResult.Comment);
                }
            }

            return motherboard;
        }
    }
}