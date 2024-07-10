using System;
using System.Collections.ObjectModel;
using Itmo.ObjectOrientedProgramming.Lab2.Entities;
using Itmo.ObjectOrientedProgramming.Lab2.Models;
using Itmo.ObjectOrientedProgramming.Lab2.Services;
using Itmo.ObjectOrientedProgramming.Lab2.Services.Validators;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab2.Tests;

public class BuildTest
{
    private readonly Repository<Motherboard> _motherboardRepository = new();
    private readonly Repository<CPU> _cpuRepository = new();
    private readonly Repository<CPUCoolingSystem> _coolerSystemRepository = new();
    private readonly Repository<RAM> _ramRepository = new();
    private readonly Repository<VideoCard> _videoCardRepository = new();
    private readonly Repository<SSD> _ssdRepository = new();
    private readonly Repository<SystemCase> _systemCaseRepository = new();
    private readonly Repository<PowerSupplyUnit> _powerUnitRepository = new();

    private readonly Collection<IComputerValidator> _computerValidators = new()
    {
        new BasicComputerValidator(),
        new CoolerCompatibilityValidator(),
        new MotherboardCompatibilityValidator(),
        new PowerUnitCompatibilityValidator(),
        new SystemCaseCompatibilityValidator(),
    };

    private readonly Collection<IComponentValidator<CPU>> _cpuValidators = new()
    {
        new CPUValidator(),
    };

    private readonly Collection<IComponentValidator<CPUCoolingSystem>> _coolerValidators = new()
    {
        new CoolerValidator(),
    };

    private readonly Collection<IComponentValidator<Motherboard>> _motherboardValidators = new()
    {
        new MotherboardValidator(),
    };

    private readonly Collection<IComponentValidator<PowerSupplyUnit>> _powerUnitValidators = new()
    {
        new PowerUnitValidator(),
    };

    private readonly Collection<IComponentValidator<RAM>> _ramValidators = new()
    {
        new RAMValidator(),
    };

    private readonly Collection<IComponentValidator<SSD>> _ssdValidators = new()
    {
        new SSDValidator(),
    };

    private readonly Collection<IComponentValidator<SystemCase>> _systemCaseValidators = new()
    {
        new SystemCaseValidator(),
    };

    private readonly Collection<IComponentValidator<VideoCard>> _videoCardValidators = new()
    {
        new VideoCardValidator(),
    };

    public BuildTest()
    {
        CPU.Builder cpuBuilder = new CPU.Builder(_cpuValidators)
            .SetName("AMD Ryzen 5 5600G")
            .SetCoresFrequency(3.9)
            .SetCoresCount(6)
            .SetSocket(new Socket("AMD AM4"))
            .SetHeatDissipation(65)
            .SetPowerConsumption(65)
            .SetMemoryFrequency(3200);
        _cpuRepository.AddComponent(cpuBuilder.Build());

        cpuBuilder.SetName("Intel Core i5-10400F")
            .SetCoresFrequency(2.9)
            .SetCoresCount(6)
            .SetSocket(new Socket("Intel 1200"))
            .SetHeatDissipation(65)
            .SetPowerConsumption(65)
            .SetMemoryFrequency(2666);
        _cpuRepository.AddComponent(cpuBuilder.Build());

        Motherboard.Builder motherboardBuilder = new Motherboard.Builder(_motherboardValidators)
            .SetName("Asus PRIME B450-PLUS")
            .SetSocket(new Socket("AMD AM4"))
            .SetPcieLinesCount(5)
            .SetSataPortsCount(6)
            .SetChipset(new Chipset("AMD B450"))
            .AddSupportedDdrStandard(DDRStandard.DDR4)
            .SetRamSlotsNumber(4)
            .SetFormFactor(FormFactor.ATX)
            .SetBIOS(new BIOS("AMI", "1.0", new Collection<CPU?> { _cpuRepository.GetComponent("AMD Ryzen 5 5600G") }));
        _motherboardRepository.AddComponent(motherboardBuilder.Build());

        motherboardBuilder.SetName("MSI Z590-A PRO")
            .SetSocket(new Socket("Intel 1200"))
            .SetPcieLinesCount(4)
            .SetSataPortsCount(6)
            .SetChipset(new Chipset("Intel Z590"))
            .AddSupportedDdrStandard(DDRStandard.DDR4)
            .SetRamSlotsNumber(4)
            .SetFormFactor(FormFactor.ATX)
            .SetBIOS(
                new BIOS("AMI", "1.0", new Collection<CPU?> { _cpuRepository.GetComponent("Intel Core i5-10400F") }));
        _motherboardRepository.AddComponent(motherboardBuilder.Build());

        CPUCoolingSystem.Builder coolerBuilder = new CPUCoolingSystem.Builder(_coolerValidators)
            .SetName("be quiet! Pure Rock LP BK034")
            .SetSize(92, 92, 45)
            .AddSupportedSockets(new Collection<Socket> { new Socket("AMD AM4") })
            .SetMaxHeatDissipation(100);
        _coolerSystemRepository.AddComponent(coolerBuilder.Build());

        coolerBuilder.SetName("Gamemax E87")
            .SetSize(85, 85, 16)
            .AddSupportedSockets(new Collection<Socket>
            { new Socket("Intel 1150"), new Socket("Intel 1155"), new Socket("Intel 1156"), new Socket("Intel 1151"), new Socket("Intel 1200") })
            .SetMaxHeatDissipation(40);
        _coolerSystemRepository.AddComponent(coolerBuilder.Build());

        RAM.Builder ramBuilder = new RAM.Builder(_ramValidators)
            .SetName("Kingston Fury Beast RGB DDR4")
            .SetMemorySize(16)
            .SetFormFactor("DIMM")
            .SetDdrStandard(DDRStandard.DDR4)
            .AddSupportedJEDECFrequency("3.2")
            .SetPowerConsumption(9);
        _ramRepository.AddComponent(ramBuilder.Build());

        VideoCard.Builder videoCardBuilder = new VideoCard.Builder(_videoCardValidators)
            .SetName("Palit GeForce RTX 4090 GameRock OC")
            .SetLength(138)
            .SetWidth(329)
            .SetVideoMemorySize(24)
            .SetPciExpressVersion("v 4.0")
            .SetChipFrequency(2610)
            .SetPowerConsumption(450);
        _videoCardRepository.AddComponent(videoCardBuilder.Build());

        SSD.Builder ssdBuilder = new SSD.Builder(_ssdValidators)
            .SetName("SSD Kingston A400 SA400S37/960G")
            .SetConnectionType(ConnectionType.SATA)
            .SetCapacity(960)
            .SetMaxSpeed(500)
            .SetPowerConsumption(1.55);
        _ssdRepository.AddComponent(ssdBuilder.Build());

        SystemCase.Builder systemCaseBuilder = new SystemCase.Builder(_systemCaseValidators)
            .SetName("Zalman i3 Edge")
            .SetMaxVideoCardLength(360)
            .SetMaxVideoCardWidth(400)
            .AddSupportedFormFactor(FormFactor.ATX)
            .SetHeight(479)
            .SetWidth(204);
        _systemCaseRepository.AddComponent(systemCaseBuilder.Build());

        PowerSupplyUnit.Builder powerUnitBuilder = new PowerSupplyUnit.Builder(_powerUnitValidators)
            .SetName("Aerocool Value VX Plus 800W")
            .SetPeakLoad(800);
        _powerUnitRepository.AddComponent(powerUnitBuilder.Build());

        powerUnitBuilder.SetName("Aerocool Value VX Plus 350W").SetPeakLoad(350);
        _powerUnitRepository.AddComponent(powerUnitBuilder.Build());
    }

    [Fact]
    public void CompatibleTest()
    {
        ComputerDirector defaultDirector = GetDefaultComputerDirector();

        Computer computer = defaultDirector.Construct();

        Assert.True(computer.Warranty);
        Assert.Null(computer.Comment);
    }

    [Theory]
    [InlineData("Aerocool Value VX Plus 350W")]
    public void WeakPowerUnitTest(string powerUnit)
    {
        ComputerDirector defaultDirector = GetDefaultComputerDirector();
        defaultDirector.SetPowerUnitName(powerUnit);

        Computer computer = defaultDirector.Construct();

        Assert.False(computer.Warranty);
    }

    [Theory]
    [InlineData("MSI Z590-A PRO", "Intel Core i5-10400F", "Gamemax E87")]
    public void WeakCoolerTest(string motherboard, string cpu, string cooler)
    {
        ComputerDirector defaultDirector = GetDefaultComputerDirector();
        defaultDirector.SetMotherboardName(motherboard)
            .SetCPUName(cpu)
            .SetCoolerName(cooler);

        Computer computer = defaultDirector.Construct();

        Assert.False(computer.Warranty);
    }

    [Theory]
    [InlineData("MSI Z590-A PRO", "Gamemax E87")]
    public void IncompatibleTest(string motherboard, string cooler)
    {
        ComputerDirector defaultDirector = GetDefaultComputerDirector();
        defaultDirector.SetMotherboardName(motherboard)
            .SetCoolerName(cooler);

        Assert.Throws<ArgumentException>(() =>
        {
            defaultDirector.Construct();
        });
    }

    private ComputerDirector GetDefaultComputerDirector()
    {
        var computerBuilder = new Computer.Builder(_computerValidators);
        var computerComponentFactory = new ComputerComponentFactory(
            new ComponentFactory<CPU>(_cpuRepository),
            new ComponentFactory<CPUCoolingSystem>(_coolerSystemRepository),
            null,
            new ComponentFactory<Motherboard>(_motherboardRepository),
            new ComponentFactory<PowerSupplyUnit>(_powerUnitRepository),
            new ComponentFactory<RAM>(_ramRepository),
            new ComponentFactory<SSD>(_ssdRepository),
            new ComponentFactory<SystemCase>(_systemCaseRepository),
            new ComponentFactory<VideoCard>(_videoCardRepository),
            null);
        var computerDirector =
            new ComputerDirector(computerBuilder, computerComponentFactory);
        computerDirector.SetMotherboardName("Asus PRIME B450-PLUS")
            .SetCPUName("AMD Ryzen 5 5600G")
            .SetCoolerName("be quiet! Pure Rock LP BK034")
            .SetRAMName("Kingston Fury Beast RGB DDR4")
            .SetVideoCardName("Palit GeForce RTX 4090 GameRock OC")
            .SetSystemCaseName("Zalman i3 Edge")
            .SetPowerUnitName("Aerocool Value VX Plus 800W")
            .SetSSDName("SSD Kingston A400 SA400S37/960G");
        return computerDirector;
    }
}